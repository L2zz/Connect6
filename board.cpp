#include <function.h>
#include <stdio.h>
#include <monte_carlo_tree_search.h>

bool userStatus = false;
char userColor = 1;
extern int cnt;
extern int best_pos1;
extern int best_pos2;

board::board() : QWidget(){

    this->x = 200;
    this->y = 60;
    startButton = new QPushButton("Game Start", this);
    startButton->setGeometry(QRect(QPoint(50, 340), QSize(100,50)));
    connect(startButton, SIGNAL (released()), this, SLOT (handleButton()));

    statusLabel = new QLabel(this);
    statusLabel->setGeometry(QRect(QPoint(65, 390), QSize(100,50)));

    update();

    int i, k;
    for(i=0; i<stoneNum; i++){
        for(k=0; k<stoneNum; k++){
            stones[i][k] = new stone(this, i, k);
            stones[i][k]->setUpdatesEnabled(false);
            stones[i][k]->setGeometry(x+40*k-20,y+40*i-20, 41, 41);
        }
    }
}

void board::handleButton(){

    userColor = 1;
    userStatus = true;
    statusLabel->setText("Your Turn");

}

void board::changeLabel(){

    int result = checkEnd(stones, (-userColor+3));

    if(result == 1){
        statusLabel->setText("You Lose!!");
    }
    else if(result == 2){
        statusLabel->setText("You Win!!");
    }
    else if(result == 0 && cnt == 2){
        userStatus = true;
        statusLabel->setText("Your Turn");
        cnt = 0;
    }
}

void board::emptyLabel(){

    int result = checkEnd(stones, userColor);

    if(result == 1){
        userStatus = false;
        statusLabel->setText("You Win!!");
    }
    else if(result == 2){
        userStatus = false;
        statusLabel->setText("You Lose!!");
    }
    else if(result == 0 && cnt == 2){
        userStatus = false;
        statusLabel->setText("computer");
        MonteCarloTreeSearch();
        QTimer::singleShot(500, this, SLOT(handleClick()));
        QTimer::singleShot(1000, this, SLOT(handleClick()));
        cnt = 0;
    }

}

void board::handleClick(){

    int i, k;

    cnt++;

    if(cnt == 1){

        k = best_pos1%stoneNum;
        i = best_pos1/stoneNum;

    }

    else{

        k = best_pos2%stoneNum;
        i = best_pos2/stoneNum;

    }

    stones[i][k]->setUpdatesEnabled(true);
    stones[i][k]->update();
    stones[i][k]->state = -userColor+3;

}



void board::paintEvent(QPaintEvent*) {

    int i;
    int size = (stoneNum-1)*stoneSize;

    QPainter painter(this);

    QPen myPen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(myPen);

    painter.setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
    painter.drawRect(x, y, size, size);
    painter.setBrush(Qt::NoBrush);

    for(i=1; i<stoneNum-1; i++){
        painter.drawLine(x, y + i*stoneSize, x+size, y+i*stoneSize);
        painter.drawLine(x + i*stoneSize, y, x + i*stoneSize, y+size);

    }

}
