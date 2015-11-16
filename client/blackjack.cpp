#include "blackjack.h"
#include "ui_blackjack.h"


extern Request request;

BlackJackClient::BlackJackClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackJackClient)
{
    ui->setupUi(this);

    set_up_poker_mapping();

    // Register custom type so QObject::connect can work
    qRegisterMetaType<WhichDeck>("WhichDeck");

    decks[WhichDeck::DECK1].deck = ui->deck1;
    decks[WhichDeck::DECK2].deck = ui->deck2;
    decks[WhichDeck::RIVAL].deck = ui->rivalCards;
    decks[WhichDeck::DEALER].deck = ui->dealerCards;

    // Add stretch to decks so they can be left-aligned and remain fix-width.
    for( int i = 0 ; i < WhichDeck::DECK_CNT; ++i )
        decks[i].deck->addStretch(1);

    // Repeatedly update rival deck configuration
    updator = new QTimer;
    updator->setInterval(Config::GameMetaUpdateFrequency);
    QObject::connect(updator,SIGNAL(timeout()),this,SLOT(update()));

    waitRivalTimer = new QTimer;
    waitRivalTimer->setInterval(Config::CheckRivalFinishFrequency);
    connect(waitRivalTimer,SIGNAL(timeout()),this,SLOT(check_rival_finish()));

    QObject::connect(ui->hitButton,   SIGNAL(clicked()),                    this, SLOT(command_hit()));
    QObject::connect(ui->standButton, SIGNAL(clicked()),                    this, SLOT(command_stand()));
    QObject::connect(ui->splitButton, SIGNAL(clicked()),                    this, SLOT(command_split()));
    QObject::connect(ui->dealButton,  SIGNAL(clicked()),                    this, SLOT(command_deal()));
    QObject::connect(ui->chooseDeck1, &QRadioButton::clicked,               [this](){ qDebug() << "Change deck to deck1"; current_deck = WhichDeck::DECK1; } );
    QObject::connect(ui->chooseDeck2, &QRadioButton::clicked,               [this](){ qDebug() << "Change deck to deck2"; current_deck = WhichDeck::DECK2; } );
    QObject::connect(this,            SIGNAL(insert_card_request(WhichDeck, int, bool)), this, SLOT(insert_card(WhichDeck, int, bool)));
    QObject::connect(this,            SIGNAL(got_rival_deck()), this, SLOT(compare_all_decks()));
}

BlackJackClient::~BlackJackClient()
{
    delete ui;
    delete updator;
    delete waitRivalTimer;
}
void BlackJackClient::cleanUp(){
    qDebug() << "Game finished!  Clean up!!";
    updator->stop();
    waitRivalTimer->stop();

    for( int i = 0; i < WhichDeck::DECK_CNT; ++i ){
        int cnt = decks[i].cards.size();
        while( cnt-- )
            pop_card((WhichDeck)i);
    }

}
void BlackJackClient::initialize(){

    qDebug() << "Initializing blackjack";

    current_deck = WhichDeck::DECK1;

    // The user cannot do anything before making his first deal
    ui->dealButton->setDefault(true);
    ui->dealButton->setDisabled(false);
    ui->splitButton->setDisabled(true);
    ui->standButton->setDisabled(true);
    ui->hitButton->setDisabled(true);

    // Initialize which deck the user acts upon
    ui->chooseDeck1->setChecked(true);
    ui->chooseDeck1->setDisabled(false);
    ui->chooseDeck2->setDisabled(true);

    ui->deck1_status->setText("");
    ui->deck2_status->setText("");

    for( int i = 0; i < WhichDeck::DECK_CNT; ++i ){
        decks[i].initialize();
    }
}

void BlackJackClient::start(){

    initialize();
    request.system( System::Request_Operation_RivalName, [this](Model::Reply* reply){
        ui->RivalName->setText(QString::fromStdString( reply->system().user().name() ));
        get_dealer_cards();
        updator->start();
        this->exec();
    });
}
void BlackJackClient::command_split(){
    ui->chooseDeck2->setDisabled(false);

    // Move the first card from deck1 to deck2
    insert_card(WhichDeck::DECK2, decks[DECK1].cards.back());
    pop_card(WhichDeck::DECK1);

    request.blackjack( BlackJack::SPLIT, [](Model::Reply* reply){});

}
void BlackJackClient::command_stand(){
    decks[ current_deck ].done = true;

    if( current_deck == WhichDeck::DECK1 ){
        ui->chooseDeck1->setDisabled(true);
        if( decks[DECK2].done || !ui->chooseDeck2->isEnabled() )
            you_are_done(get_your_best_deck());
    }
    else{
        ui->chooseDeck2->setDisabled(true);
        if( decks[DECK1].done || !ui->chooseDeck1->isEnabled() )
            you_are_done(get_your_best_deck());
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
        qDebug() << "asking hit: " << QString::number(card) ;
        emit insert_card_request(current_deck, card);
    });
}
void BlackJackClient::command_deal(){
    request.blackjack( BlackJack::DEAL, [this](Model::Reply* reply){
        int card1 = reply->blackjack().card1(), card2 = reply->blackjack().card2();
        emit insert_card_request(current_deck, card1);
        emit insert_card_request(current_deck, card2);
        if( same_card_type(card1,card2) ){
            // Enable the player to split
            ui->splitButton->setDisabled(false);
        }
    });

    // The deal button is only used for the first deal
    ui->dealButton->setDisabled(true);
    ui->standButton->setDisabled(false);
    ui->hitButton->setDisabled(false);

    // Player can repeatedly issue "hit" from now on
    ui->hitButton->setDefault(true);
}

void BlackJackClient::get_dealer_cards(){
    request.blackjack( BlackJack::GET_DEALER_DECK, [this](Model::Reply* reply){
        const auto& r = reply->blackjack();
        int size = r.cards_size();
        for( int i = 0; i < size ; ++i ){
            emit insert_card_request(WhichDeck::DEALER, r.cards(i), /*mask the card*/true );
        }

    });
}
void BlackJackClient::you_are_done(WhichDeck yourBestDeck){

    ui->splitButton->setDisabled(true);
    ui->standButton->setDisabled(true);
    ui->hitButton->setDisabled(true);

    // Tell backend your result
    bool deck2_the_best = ( yourBestDeck == WhichDeck::DECK2 );
    request.blackjack_set_finish( deck2_the_best, [](Model::Reply* reply){});

    qDebug() << "Checking if rival has done";

    // Check whether your rival has done
    request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
        if(reply->status()){
            // Your rival has already done, so let's announce the result!
            qDebug() << "Your rival has done";
            game_finish();
        }
        else{
            // You are done before your rival!  Now wait for your rival.
            qDebug() << "Your rival has not done";
            emit waitForRival();
            waitRivalTimer->start();
        }

        updator->stop();
    });
}
void BlackJackClient::game_finish(){

    // Fetch rival's cards
    request.blackjack( BlackJack::GET_RIVAL_DECK, [this](Model::Reply* reply){

        const auto & b = reply->blackjack();

        /* Remove all the place-holder masked cards */
        int cnt = decks[RIVAL].cards.size();
        while( cnt-- )
            pop_card(WhichDeck::RIVAL);

        /* Update rival's cards to its final state */

        for( int i = 0; i < b.cards_size(); ++i ){
            qDebug() << "Inserting rival card: " << b.cards(i);
            emit insert_card_request(WhichDeck::RIVAL, b.cards(i) );
        }

        emit got_rival_deck();
    });

    // Display dealer's card
    int cnt = decks[WhichDeck::DEALER].cards.size();
    for( int i = 0; i < cnt; ++i ){
        QLabel* card = (QLabel*) ui->dealerCards->itemAt(i)->widget();
        card->setText(convert_card(decks[WhichDeck::DEALER].cards[i]));
    }
}
void BlackJackClient::compare_all_decks(){

    auto yourBest = get_your_best_deck();

    // Compare your deck with dealer
    int you_vs_dealer = compare_deck(yourBest, WhichDeck::DEALER);
    // Compare your deck with your rival
    int you_vs_rival = compare_deck(yourBest, WhichDeck::RIVAL);

    // And show the result
    emit showBlackjackResult( you_vs_dealer, you_vs_rival );

    // Modify money
    modify_money(you_vs_dealer);
    modify_money(you_vs_rival);
}

void BlackJackClient::check_rival_finish(){
    request.system( System::Request_Operation_CheckFinish, [this](Model::Reply* reply){
        if( reply->system().user().dead() ){
            emit rival_die();
            return;
        }
        if(reply->status()){
            // Your rival has finished
            waitRivalTimer->stop();
            game_finish();
        }
        else{
            qDebug() << "Your rival not finished";
        }
    });
}


void BlackJackClient::check_result(WhichDeck deckType){
    static const QString busted("<strong><font color=red>Busted!</font></strong>");
    static const QString blackjack("<strong><font color=green>Blackjack!</font></strong>");

    // If both decks are busted, the game is over.

    switch(deckType){
        case DECK1:
            qDebug() << "Checking deck1 result";
            if( decks[DECK1].busted() ){
                ui->deck1_status->setText(busted);
                if( !ui->chooseDeck2->isEnabled() ){
                    you_are_done(WhichDeck::DECK1);
                    break;
                }
                if( decks[DECK2].done )
                    you_are_done(WhichDeck::DECK2);
            }
            else if( decks[DECK1].blackjack() ){
                ui->deck1_status->setText(blackjack);
                you_are_done(WhichDeck::DECK1);
            }
            break;
        case DECK2:
            qDebug() << "Checking deck2 result";
            if( decks[DECK2].busted() ){
                ui->deck2_status->setText(busted);
                if( !ui->chooseDeck1->isEnabled() ){
                    you_are_done(WhichDeck::DECK2);
                    break;
                }
                if( decks[DECK1].done )
                    you_are_done(WhichDeck::DECK1);
            }
            else if( decks[DECK2].blackjack() ){
                ui->deck2_status->setText(blackjack);
                you_are_done(WhichDeck::DECK2);
            }

    }
}
BlackJackClient::WhichDeck BlackJackClient::get_your_best_deck(){
    if( compare_deck(WhichDeck::DECK1, WhichDeck::DECK2) >= 0 )
        return WhichDeck::DECK1;
    else
        return WhichDeck::DECK2;
}


int BlackJackClient::compare_deck(WhichDeck a, WhichDeck b){

    qDebug() << "Comparing two decks: ";

    // If both are busted
    if(decks[a].busted() && decks[b].busted() ){
        qDebug() << "Both busted";
        return 0;
    }

    // If only one deck is under consideration
    if(decks[a].busted() && decks[b].has_card() ){
        qDebug() << "The first deck busted";
        return -1;
    }
    if(decks[b].busted() && decks[a].has_card() ){
        qDebug() << "The second deck busted";
        return 1;
    }

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
        if( !a_blackjack && b_blackjack )
            return -1;
    }

    return 0;
}
void BlackJackClient::insert_card(enum WhichDeck deckType, int value, bool masked ){
    static QString style("font-size: 18px; font-weight: bold; border: 1px solid grey; text-align: center;");

    auto card = new QLabel;
    card->setAlignment(Qt::AlignCenter);
    card->setFixedSize(110, 60);
    card->setText(masked ? QString("?") : convert_card(value));
    card->setStyleSheet(style);

    decks[ deckType ].insert(value);
    decks[ deckType ].deck->insertWidget(0, card);

    switch(deckType){
        case DECK1:
        case DECK2:
            check_result(deckType);
    }
}
void BlackJackClient::pop_card(WhichDeck deckType){

    decks[ deckType ].pop();

    QLayoutItem *card = decks[deckType].deck->takeAt(0);

    if(card && card->widget()){
        delete card->widget();
        delete card;
    }
}

void BlackJackClient::mark_new_card( QLabel* new_card ){
    static const QString style("font-size: 18px; font-weight: bold; border: 1px solid grey; text-align: center;");
    static const QString tmp_style(style + "background-color: rgb(255,208,127); border-width:2px;");

    new_card->setStyleSheet(tmp_style);

    QTimer *timer = new QTimer;
    timer->setSingleShot(true);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        new_card->setStyleSheet(style);
        timer->deleteLater();
    } );

    timer->start(1500);

}
void BlackJackClient::update(){
    request.blackjack( BlackJack::UPDATE, [this](Model::Reply* reply){
        qDebug() << "Got rival meta";
        if( reply->blackjack().dead() ){
            emit rival_die();
            return;
        }
        if( reply->blackjack().has_count() ){
            qDebug() << "Received rival size: " << QString::number(reply->blackjack().count());

            int diff = reply->blackjack().count() - decks[RIVAL].cards.size() ;
            for( int i = 0; i < diff; ++i )
                emit insert_card_request(WhichDeck::RIVAL, 0, /*mask the card*/true );
        }
    });
}

void BlackJackClient::modify_money(int result){

    if( result > 0 )
        emit modify_player_money( Config::BlackjackBet );
    else if( result == 0 )
        emit modify_player_money( Config::BlackjackBet / 2 );

}
QString BlackJackClient::convert_card( int card_val ){
    int mod = card_val%13, div = card_val/13;
    return card_type_mapping[ mod == 0 ? div-1 : div ] + " " + card_val_mapping[ mod ];
}
void BlackJackClient::set_up_poker_mapping(){
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
    if( point > 21 ){
        done = true;
        return true;
    }
    return false;
}
bool DeckInfo::has_card(){
    return cards.size() > 0;
}

bool DeckInfo::blackjack(){
    if( point == 11 && ace_cnt == 1 ){
        done = true;
        return true;
    }
    return false;
}

void DeckInfo::insert(int value){
    qDebug() << "Inserting card with index" << QString::number(value);
    value = BlackJackClient::card_value(value);
    qDebug() << "and value " << QString::number(value);
    qDebug() << "current value: " << point + value;
    point += value;
    cards.push_back(value);
    if(value == 1)
        ++ace_cnt;
}
void DeckInfo::pop(){
    int value = BlackJackClient::card_value(cards.back());
    qDebug() << "Popping card with value: " << value;
    qDebug() << "current value: " << point - value;
    point -= value;

    if( value == 1 )
        --ace_cnt;
    cards.pop_back();
}
int DeckInfo::best_score(){
    int best_score = point;
    for( int i = 0; i < ace_cnt; ++i, best_score += 10 )
        if( best_score + 10 > 21 )
            break;

    return best_score;
}
void DeckInfo::initialize(){
    cards.clear();
    ace_cnt = point = 0;
    done = false;
}
bool BlackJackClient::same_card_type( int card1, int card2 ){
    return (card1 % 13) == (card2 % 13);
}
int BlackJackClient::card_value( int card ){

    int mod = card % 13;
    if( mod == 0 || mod > 10 ) /* J, Q, K */
        return 10;
    return mod;
}

// This function is triggered when user close the window
void BlackJackClient::reject()
{
    qDebug() << "Closing the window.  Quitting game";
    request.system( System::Request_Operation_QuitRoom, [this](Model::Reply* reply){
        QDialog::reject();
    });

}
