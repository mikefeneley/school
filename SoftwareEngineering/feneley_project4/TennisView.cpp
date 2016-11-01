#include "TennisView.h"

/*
 * Intialize TennisView and set screen properties.
 */
TennisView::TennisView(QWidget *parent, TennisModel *model) : QWidget(parent)
{
	tennis_model = model;
	resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(Pal);
	show();
}
/*
 * Calls paintEvent to repaint board after changes
 * to the game model.
 */
void TennisView::RefreshDisplay()
{
    update();
}
/*
 * Paints all game objects on the game board including player scores,
 * the game boll, and the player paddles.
 */
void TennisView::paintEvent(QPaintEvent* event)
{    

	// Paint border around draw area.
    QPainter painter(this);

    painter.setPen(Qt::white);

    // Draw midpoint line on the screen.
    int midpoint = WINDOW_WIDTH / 2;
    for(int i = 0; i < WINDOW_HEIGHT; i+= MID_RECT_LENGTH * 2)
    {
    	painter.drawLine(midpoint, i, midpoint, i+MID_RECT_LENGTH);

    }


    // Draw game objects on screen.
    painter.drawRect(tennis_model->player1);
    painter.drawRect(tennis_model->player2);
    QBrush *white_brush = new QBrush(Qt::white);
    painter.setBrush(*white_brush);
    painter.drawEllipse(tennis_model->ball, BALL_RADIUS, BALL_RADIUS);

    // Draw score
    QString player1 = GetPlayer1Score();
    QString player2 = GetPlayer2Score();
    painter.drawText(QPoint(PLAYER1_SCORE_X, FONT_SIZE), player1);
    painter.drawText(QPoint(PLAYER2_SCORE_X, FONT_SIZE), player2);
}
/*
 * Parse player1 score and return value as string. 
 */
QString TennisView::GetPlayer1Score()
{
    int score = tennis_model->player1_score;

    switch(score) {
        case(0):
            return "0";
        case(1):
            return "1";
        case(2):
            return "2";
        case(3):
            return "3";    
        case(4):
            return "4";   
        case(5):
            return "5";   
        case(6):
            return "6";   
        case(7):
            return "7";   
        case(8):
            return "8";   
        case(9):
            return "9";   
        default:
            return "-1";
    }
    return "-1";
}

/*
 * Parse player2 score and return value as string. 
 */
QString TennisView::GetPlayer2Score()
{
    int score = tennis_model->player2_score;
    switch(score) {
        case(0):
            return "0";
        case(1):
            return "1";
        case(2):
            return "2";
        case(3):
            return "3";    
        case(4):
            return "4";   
        case(5):
            return "5";   
        case(6):
            return "6";   
        case(7):
            return "7";   
        case(8):
            return "8";   
        case(9):
            return "9";      
        default:
            return "-1";
    }
    return "-1";
}