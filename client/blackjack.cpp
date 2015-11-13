#include "blackjack.h"
#include "ui_blackjack.h"
#include "request.h"
#include "config.h"

extern Request request;

BlackJackClient::BlackJackClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackJackClient)
{
    ui->setupUi(this);

    setUpPokerMapping();

    // Register custom type so QObject::connect can work
    qRegisterMetaType<WhichDeck>("WhichDeck");

    // Repeatedly update rival deck configuration
    updator = new QTimer;
    updator->setInterval(Config::GameMetaUpdateFrequency);
    QObject::connect(updator,SIGNAL(timeout()),this,SLOT(update()));

    waitRivalTimer = new QTimer;
    waitRivalTimer->setInterval(Config::CheckRivalFinishFrequency);
    connect(waitRivalTimer,SIGNAL(timeout()),this,SLOT(checkRivalFinish()));


    // The user cannot do anything before making his first deal
    ui->dealButton->setDefault(true);
    ui->splitButton->setDisabled(true);
    ui->standButton->setDisabled(true);
    ui->hitButton->setDisabled(true);

    // Initialize which deck the user acts upon
    ui->chooseDeck1->setChecked(true);
    ui->chooseDeck2->setDisabled(true);

    // Add stretch to decks so they can be left-aligned and remain fix-width.
    ui->deck1->addStretch(1);
    ui->deck2->addStretch(1);
    ui->rivalCards->addStretch(1);
    ui->dealerCards->addStretch(1);

    current_deck = WhichDeck::DECK1;

    QObject::connect(waitRivalTimer,  SIGNAL(timeout()),                    this,SLOT(checkRivalFinish()));
    QObject::connect(ui->hitButton,   SIGNAL(clicked()),                    this, SLOT(command_hit()));
    QObject::connect(ui->standButton, SIGNAL(clicked()),                    this, SLOT(command_stand()));
    QObject::connect(ui->splitButton, SIGNAL(clicked()),                    this, SLOT(command_split()));
    QObject::connect(ui->dealButton,  SIGNAL(clicked()),                    this, SLOT(command_deal()));
    QObject::connect(ui->chooseDeck1, &QRadioButton::clicked,               [this](){ current_deck = WhichDeck::DECK1; } );
    QObject::connect(ui->chooseDeck2, &QRadioButton::clicked,               [this](){ current_deck = WhichDeck::DECK2; } );
    QObject::connect(this,            SIGNAL(insert_card_request(WhichDeck, int, bool)), this, SLOT(insert_card(WhichDeck, int, bool)));
}

BlackJackClient::~BlackJackClient()
{ 
    delete ui;
}
void BlackJackClient::cleanUp(){
    updator->stop();
    waitRivalTimer->stop();
    delete updator;
    delete waitRivalTimer;
}
void BlackJackClient::start(){
    request.system( System::Request_Operation_RivalName, [this](Model::Reply* reply){
        ui->RivalName->setText(QString::fromStdString( reply->system().user().name() ));
        getDealerCards();
        updator->start();
        this->exec();
    });
}
void BlackJackClient::command_split(){
    ui->chooseDeck2->setDisabled(false);

    // Move the first card from deck1 to deck2
    pop_card(WhichDeck::DECK1);
    insert_card(WhichDeck::DECK2, decks[DECK1].cards.back());
    decks[DECK1].pop();

    request.blackjack( BlackJack::SPLIT, [](Model::Reply* reply){});

}
void BlackJackClient::command_stand(){
    if( current_deck == WhichDeck::DECK1 ){
        ui->chooseDeck1->setDisabled(true);
        if( !ui->chooseDeck2->isEnabled() )
            youAreDone(get_your_best_deck());
    }
    else{
        ui->chooseDeck1->setDisabled(true);
        if( !ui->chooseDeck1->isEnabled() )
            youAreDone(get_your_best_deck());
    }
}
void BlackJackClient::command_hit(){
    qDebug() << "Asking for the a HIT";

    // The player is no longer able to issue hit once busted or gotten blackjack.
    if( (current_deck == WhichDeck::DECK1 && decks[DECK1].done) ||
        (current_deck == WhichDeck::DECK2 && decks[DECK2].done) )
        return;

    bool acted_on_deck2 = current_deck == WhichDeck::DECK2;
    request.blackjack_hit( acted_on_deck2, [this](Model::Reply* reply){
        int card = reply->blackjack().card1();
        qDebug() << "Got hit: " << QString::number(card) ;
        emit insert_card_request(current_deck, card);
    });
}
void BlackJackClient::command_deal(){

    // The deal button is only used for the first deal
    ui->dealButton->setDisabled(true);
    ui->standButton->setDisabled(false);
    ui->hitButton->setDisabled(false);

    // Player can repeatedly issue "hit" from now on
    ui->hitButton->setDefault(true);

    qDebug() << "Asking for the first deals";
    request.blackjack( BlackJack::DEAL, [this](Model::Reply* reply){
        int card1 = reply->blackjack().card1(), card2 = reply->blackjack().card2();
        emit insert_card_request(current_deck, card1);
        emit insert_card_request(current_deck, card2);
        if( card_value(card1) == card_value(card2) ){
            // Enable the player to split
            ui->splitButton->setDisabled(false);
        }
    });

}

void BlackJackClient::getDealerCards(){
    request.blackjack( BlackJack::GET_RIVAL_DECK, [this](Model::Reply* reply){
        qDebug() << "Got dealer status ";
        const auto& r = reply->blackjack();
        int size = r.cards_size();
        for( int i = 0; i < size ; ++i ){
            emit insert_card_request(WhichDeck::DEALER, r.cards(i), /*mask the card*/true );
        }

    });
}
void BlackJackClient::youAreDone(WhichDeck yourBestDeck){

    // Tell backend your result
    bool deck2_the_best = ( yourBestDeck == WhichDeck::DECK2 );
    request.blackjack_set_finish( deck2_the_best, [this](Model::Reply* reply){});

    QThread::sleep(2000);

    // Check whether your rival has done
    request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
        if(reply->status()){
            // Your rival has already done, so let's announce the result!
            gameFinish();
        }
        else{
            // You are done before your rival!  Now wait for your rival.
            waitRivalTimer->start();
        }

        updator->stop();
    });
}
void BlackJackClient::gameFinish(){

    request.blackjack( BlackJack::GET_RIVAL_DECK, [this](Model::Reply* reply){
        auto yourBest = get_your_best_deck();
        const auto & b = reply->blackjack();
        int cnt = decks[RIVAL].cards.size();

        /* Remove all the place-holder cards */
        while( cnt-- )
            pop_card(WhichDeck::RIVAL);

        /* Update rival's cards to its final state */
        for( int i = 0; i < b.cards_size(); ++i )
            emit insert_card_request(WhichDeck::RIVAL, b.cards(i) );

        // Compare your deck with dealer
        int you_vs_dealer = compare_deck(yourBest, WhichDeck::DEALER);
        // Compare your deck with your rival
        int you_vs_rival = compare_deck(yourBest, WhichDeck::RIVAL);

        // And show the result
        emit showBlackjackResult( you_vs_dealer, you_vs_rival );

        // Modify money
        modifyMoney(you_vs_dealer);
        modifyMoney(you_vs_rival);
    });

}
void BlackJackClient::checkRivalFinish(){
    request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
        if(reply->status()){
            // Your rival has finished
            waitRivalTimer->stop();
            gameFinish();
        }
    });
}
void BlackJackClient::update(){
    request.blackjack( BlackJack::UPDATE, [this](Model::Reply* reply){
        qDebug() << "Got rival meta";
        if( reply->blackjack().has_count() ){
            qDebug() << "Received rival size: " << QString::number(reply->blackjack().count());

            int diff = reply->blackjack().count() - decks[RIVAL].cards.size() ;
            for( int i = 0; i < diff; ++i )
                emit insert_card_request(WhichDeck::RIVAL, 0, /*mask the card*/true );

        }
    });
}

QString BlackJackClient::convert_card( int card_val ){
    int mod = card_val%13, div = card_val/13;
    return card_type_mapping[ mod == 0 ? div-1 : div ] + " " + card_val_mapping[ mod ];
}
void BlackJackClient::check_result(WhichDeck deckType){
    static const QString busted("<strong><font color=red>Busted!</font></strong>");
    static const QString blackjack("<strong><font color=green>Blackjack!</font></strong>");

    // If both decks are busted, the game is over.
    switch(deckType){
        case DECK1:
            if( decks[DECK1].busted() ){
                ui->deck1_status->setText(busted);
                if( decks[DECK2].done )
                    youAreDone(WhichDeck::DECK2);
            }
            else if( decks[DECK1].blackjack() ){
                ui->deck1_status->setText(blackjack);
                youAreDone(WhichDeck::DECK1);
            }
            break;
        case DECK2:
            if( decks[DECK2].busted() ){
                ui->deck2_status->setText(busted);
                if( decks[DECK1].done )
                    youAreDone(WhichDeck::DECK1);
            }
            else if( decks[DECK2].blackjack() ){
                ui->deck2_status->setText(blackjack);
                youAreDone(WhichDeck::DECK2);
            }
            break;
    }
}
BlackJackClient::WhichDeck BlackJackClient::get_your_best_deck(){
    if( compare_deck(WhichDeck::DECK1, WhichDeck::DECK2) >= 0 )
        return WhichDeck::DECK1;
    else
        return WhichDeck::DECK2;
}
void BlackJackClient::modifyMoney(int result){

    if( result > 0 )
        emit modifyPlayerMoney( Config::BlackjackBet );
    else if( result == 0 )
        emit modifyPlayerMoney( 2 * Config::BlackjackBet );

}

int BlackJackClient::compare_deck(WhichDeck a, WhichDeck b){
    if(decks[a].busted())
        return -1;
    if(decks[b].busted())
        return 1;

    int a_best = decks[a].best_score();
    int b_best = decks[b].best_score();

    if( a_best > b_best )
        return 1;
    if( a_best < b_best )
        return -1;

    // They have the same score
    if( a_best == 21 ){
        bool a_blackjack = decks[a].blackjack(), b_blackjack = decks[b].blackjack();
        if( a_blackjack && !b_blackjack )
            return 1;
        if( a_blackjack && !b_blackjack )
            return -1;
    }

    return 0;
}
void BlackJackClient::pop_card(WhichDeck deckType){
    
    decks[ deckType ].pop();

    switch(deckType){
        case RIVAL:
            ui->rivalCards->removeWidget( ui->rivalCards->takeAt(0)->widget() );
            break;
        case DECK1:
            ui->deck1->removeWidget( ui->deck1->takeAt(0)->widget() );
            break;
        case DEALER:
            ui->dealerCards->removeWidget( ui->dealerCards->takeAt(0)->widget() );
            break;
    }
}

void BlackJackClient::insert_card(enum WhichDeck deckType, int value, bool masked ){
    auto card = new QLabel;
    card->setAlignment(Qt::AlignCenter);
    card->setFixedSize(110, 60);
    card->setText(masked ? QString("?") : convert_card(value));

    switch(deckType){
        case DECK1:
            ui->deck1->insertWidget(0, card);
            check_result(WhichDeck::DECK1);
            break;
        case RIVAL:
            ui->rivalCards->insertWidget(0, card);
            break;
        case DECK2:
            ui->deck2->insertWidget(0, card);
            check_result(WhichDeck::DECK2);
            break;
        case DEALER:
            ui->dealerCards->insertWidget(0, card);
            break;
    }

    decks[ deckType ].insert(value);

    // Emphasizing the insertion of a new card.
    mark_new_card(card);
}


void BlackJackClient::mark_new_card( QLabel* new_card ){
    QString style("font-size: 18px; font-weight: bold; border: 1px solid grey; text-align: center;");
    new_card->setStyleSheet( style + "background-color: rgb(255,208,127); border-width:2px;" );

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        new_card->setStyleSheet(style);
        timer->deleteLater();
      } );

    timer->start(1000);
}

void BlackJackClient::setUpPokerMapping(){
    card_type_mapping[0] = QString("Club");
    card_type_mapping[1] = QString("Diamond");
    card_type_mapping[2] = QString("Heart");
    card_type_mapping[3] = QString("Spade");

    card_val_mapping[11] = QString("J");
    card_val_mapping[12] = QString("Q");
    card_val_mapping[0] = QString("K");
    for(int i = 1; i <= 10; ++i )
        card_val_mapping[i] = QString::number(i);
}

bool DeckInfo::busted(){
    if( point > 21 )
        return done = true;
    return false;
}

bool DeckInfo::blackjack(){
    if( point == 11 && ace_cnt == 1 )
        return done = true;
    return false;
}

void DeckInfo::insert(int value){
    value = BlackJackClient::card_value(value);
    point += value;
    cards.push_back(value);
    if(value == 1)
        ++ace_cnt;
}
void DeckInfo::pop(){
    int value = BlackJackClient::card_value(cards.back());
    if( value == 1 )
        --ace_cnt;
    point -= value;
    cards.pop_back();
}
int DeckInfo::best_score(){
    int best_score = point;
    for( int i = 0; i < ace_cnt; ++i, best_score += 9 )
        if( best_score + 9 > 21 )
            break;

    return best_score;
}
int BlackJackClient::card_value( int card ){

    int mod = card % 13;
    if( mod == 0 || mod > 10 ) /* J, Q, K */
        return 10;
    return mod;
}
