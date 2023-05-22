#ifndef GAME_EVENTS
#define GAME_EVENTS

#include "EventManager.h"
#include "Vector2.h"

class OnRenderEvent : BaseEvent
{
public:

	static EventType GetStaticType();
	OnRenderEvent() {};

	EventType GetType() const override
	{
		return GetStaticType();
	}

};

class OnClickEvent : BaseEvent
{
public:
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int button, state, x, y;

	OnClickEvent(int button, int state, int x, int y)
	{
		this->button = button;
		this->state = state;
		this->x = x;
		this->y = y;
	}
};

class OnMouseOverEvent : BaseEvent
{
private:
	static int oldX, oldY;

public:
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int x, y, wheel;
	Vector2 translation;

	OnMouseOverEvent(int x, int y, int wheel)
	{
		this->x = x;
		this->y = y;
		this->wheel = wheel;

		translation = Vector2(x - oldX, y - oldY);
		oldX = x;
		oldY = y;
	}
};

class OnKeyEvent : BaseEvent
{
public:
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int key;
	int state;

	OnKeyEvent(int key, int state)
	{
		this->key = key;
		this->state = state;
	}
};

// Calback classes - essas classes podem ser herdadas para para implementar eventos genéricos como renderização, clique etc.

class IRenderable
{
protected:
	
	//define a ordem de renderização dos objetos
	enum GameLayer
	{
		UI2 = 0,
		UI,
		Default,
		LayersCount
	};

public:
	static void RenderAll(BaseEvent* baseEvent);

	virtual GameLayer GetLayer()
	{
		return GameLayer::Default;
	}

private:
	static std::list<IRenderable*> renderList;
	virtual void OnRender(OnRenderEvent* args) = 0;

protected:

	IRenderable()
	{
		renderList.remove(this);
	}

	~IRenderable()
	{
		renderList.push_back(this);
	}
};

class IClickable
{
private:
	static std::list<IClickable*> clickList;
	virtual void OnClick(OnClickEvent* args) = 0;
	virtual void OnMouseOver(OnMouseOverEvent* args) = 0;

public:
	static void ClickAll(BaseEvent* baseEvent);
	static void MouseOverAll(BaseEvent* baseEvent);

protected:
	IClickable()
	{
		clickList.push_back(this);
	}

	~IClickable()
	{
		clickList.remove(this);
	}
};

class IKeyable
{
private:
	static std::list<IKeyable*> keyList;
	virtual void OnKey(OnKeyEvent* args) = 0;

public:
	static void KeyAll(BaseEvent* baseEvent);

protected:
	IKeyable()
	{
		keyList.push_back(this);
	}
	~IKeyable()
	{
		keyList.remove(this);
	}
};

#endif // !GAME_EVENTS
