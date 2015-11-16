#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QTimer>
#include <QRadioButton>
#include <QThread>
#include <QRadioButton>
#include <QHBoxLayout>
#include <array>
#include <vector>
#include "request.h"
#include "config.h"
#include "main.model.pb.h"

namespace Ui {
    class BlackJackClient;
}

struct DeckInfo {
    // Fields
    int ace_cnt; int point;
    bool done;
    QHBoxLayout* deck;
    std::vector<int> cards;

    // Methods
    DeckInfo():ace_cnt(0),point(0), done(false){}
    bool busted();
    bool blackjack();
    bool has_card();
    void pop();
    int best_score();
    void insert(int value);
    void initialize();
};

class BlackJackClient : public QDialog
{
    Q_OBJECT

    enum WhichDeck { RIVAL = 0, DEALER, DECK1, DECK2, DECK_CNT };

public:
    explicit BlackJackClient(QWidget *parent = 0);
    ~BlackJackClient();
    void start();
    static int card_value( int card );
    static bool same_card_type( int card1, int card2 );

signals:
    void insert_card_request(WhichDeck deckType, int value, bool masked = false);
    void modify_player_money(int);
    void got_rival_deck();
    void rival_die();
    void showBlackjackResult(int,int);
    void waitForRival();


public slots:
    void cleanUp();
    void reject();

private slots:
    void command_stand();
    void command_hit();
    void command_split();
    void command_deal();
    void update();
    void check_rival_finish();
    void insert_card(WhichDeck deckType, int value, bool masked = false);
    void game_finish();
    void compare_all_decks();


private:
    void initialize();
    void set_up_poker_mapping();
    void get_dealer_cards();
    void check_result(WhichDeck deckType);
    void mark_new_card( QLabel* new_card );
    void you_are_done(WhichDeck deckType);
    WhichDeck get_your_best_deck();
    QString convert_card( int card_val );
    void pop_card(WhichDeck deckType);
    int compare_deck(WhichDeck a, WhichDeck b);
    void modify_money(int result);


    /* Fields */
    Ui::BlackJackClient *ui;
    QTimer* updator;
    QTimer* waitRivalTimer;

    WhichDeck current_deck;
    std::array< DeckInfo, 4 > decks;
    
    std::array< QString, 13 > card_val_mapping;
    std::array< QString, 4 > card_type_mapping;


};

#endif // BLACKJACK_H
