#include "Window.h"

/**
 * Initializes main window pannel.
 *
 * Post: Model View and Controller have been created with slots
 *		 signals linked.
 *       Window size has been set.         
 */
Window::Window()
{
	srand(time(NULL));

	model = new TennisModel();
	view = new TennisView(this, model);
	controller = new TennisController(this, model);
	timer = new QTimer(this);


    connect(timer, SIGNAL(timeout(void)), controller, SLOT(EngineUpdate(void)));
	connect(controller, SIGNAL(GameChange(void)), view, SLOT(RefreshDisplay(void)));

	this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->show();
	timer->start(UPDATE_SPEED);
}

/**
 * Send all key presses to the game controller.
 */
void Window::keyPressEvent(QKeyEvent *event)
{
	controller->KeyEvent(event);
}