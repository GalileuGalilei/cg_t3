/*********************************************************************
// Canvas2D
// Autor: Cesar Tadeu Pozzer
//        04/2021
// *******************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "EventManager.h"
#include "GameEvents.h"
#include <time.h>
#include "Scenary.h"

void keyboard(int key) 
{
    OnKeyEvent keyEvent = OnKeyEvent(key, 0);
    EventManager::Instance()->InvokeEvent<OnKeyEvent>((BaseEvent*)&keyEvent);
}

void keyboardUp(int key) 
{
    OnKeyEvent keyEvent = OnKeyEvent(key, 1);
	EventManager::Instance()->InvokeEvent<OnKeyEvent>((BaseEvent*)&keyEvent);
}

void render()
{
    OnRenderEvent renderEvent = OnRenderEvent();
    EventManager::Instance()->InvokeEvent<OnRenderEvent>((BaseEvent*)&renderEvent);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (state != -2)
    {
        OnClickEvent clickEvent = OnClickEvent(button, state, x, y);
        EventManager::Instance()->InvokeEvent<OnClickEvent>((BaseEvent*)&clickEvent);
    }

    OnMouseOverEvent mouseOverEvent = OnMouseOverEvent(x, y, direction);
    EventManager::Instance()->InvokeEvent<OnMouseOverEvent>((BaseEvent*)&mouseOverEvent);
}

int main(void)
{
    int screenWidth = 920, screenHeight = 640;
    srand(time(NULL));

    EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
    EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
    EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);
    EventManager::Instance()->AddListener<OnKeyEvent>(IKeyable::KeyAll);

    Scenary* scenary = new Scenary(Vector2(0, 0), Vector2(screenWidth, 0), Vector2(0, screenHeight));

    CV::init(&screenWidth, &screenHeight, "CGT3 - Galaga");
    CV::run();
}
