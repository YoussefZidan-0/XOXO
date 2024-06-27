#include <QtTest/QtTest>
#include "board.h"

class TestBoard : public QObject {
    Q_OBJECT

private slots:
    // Unit tests
    void testPlayerXWins();
    void testPlayerOWins();
    void testDraw();

    // Integration tests
    void testFullGameFlow();
};

#endif // TEST_BOARD_H
