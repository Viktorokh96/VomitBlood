#ifndef _IVIEW_HPP
#define _IVIEW_HPP

class IView {
public:
	virtual ~IView() {}
	virtual void draw() = 0;
	virtual cmd_t update() = 0;
};

#endif
