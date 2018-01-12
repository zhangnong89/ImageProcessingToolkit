#ifndef PUZZLESETTING
#define PUZZLESETTING
#include"all.h"
//拼图设置页
class PuzzleSettingPage: public QScrollArea
{
    Q_OBJECT

public:
    explicit PuzzleSettingPage(QWidget *parent = 0);
    QPushButton *templatePuzzle;
    QPushButton *freePuzzle;
    QPushButton *optionPuzzle;
//    void paintEvent(QPaintEvent *e);
    ~PuzzleSettingPage();

    QPushButton *puzzle_1;
    QPushButton *puzzle_2;
    QPushButton *puzzle_3;
    QPushButton *puzzle_4;
    QPushButton *puzzle_openNewFile;
    QPushButton *puzzle_save;
    QVBoxLayout *puzzleTemplateLayout;
    QVBoxLayout *puzzleOptionLayout;

signals:
    void sig_templatePuzzlePress();
    void sig_puzzle_1();
    void sig_puzzle_2();
    void sig_puzzle_3();
    void sig_puzzle_4();
    void sig_puzzle_openNewFile();
    void sig_puzzle_save();
    void sig_freePuzzlePress();
public slots:
    void slot_puzzle_saveSuccess();

};
#endif // PUZZLESETTING

