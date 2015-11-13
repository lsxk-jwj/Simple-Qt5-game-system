#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QTimer>
#include <QRadioButton>
#include <QThread>
#include <QRadioButton>
#include <array>
#include <vector>

namespace Ui {
    class BlackJackClient;
}

struct DeckInfo {
    // Fields
    int ace_cnt; int point;
    bool done;
    std::vector<int> cards;

    // Methods
    DeckInfo():ace_cnt(0),point(0), done(false){}
    bool busted();
    bool blackjack();
    void pop();
    int best_score();
    void insert(int value);
};

class BlackJackClient : public QDialog
{
    Q_OBJECT

    enum WhichDeck { RIVAL = 0, DEALER, DECK1, DECK2 };
    enum GameResult { LOSE, WIN, NotKnownYet };

public:
    explicit BlackJackClient(QWidget *parent = 0);
    ~BlackJackClient();
    void start();
    static int card_value( int card );

signals:
    void insert_card_request(WhichDeck deckType, int value, bool masked = false);
    void modifyPlayerMoney(int);
    void showBlackjackResult(int,int);

public slots:
    void cleanUp();

private slots:
    void command_stand();
    void command_hit();
    void command_split();
    void command_deal();
    void update();
    void checkRivalFinish();
    void insert_card(WhichDeck deckType, int value, bool masked = false);
    void gameFinish();


private:
    void setUpPokerMapping();
    void getDealerCards();
    void check_result(WhichDeck deckType);
    void mark_new_card( QLabel* new_card );
    void youAreDone(WhichDeck deckType);
    WhichDeck get_your_best_deck();
    QString convert_card( int card_val );
    void pop_card(WhichDeck deckType);
    int compare_deck(WhichDeck a, WhichDeck b);
    void modifyMoney(int result);

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
