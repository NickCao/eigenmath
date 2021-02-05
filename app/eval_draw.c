#include "app.h"

#define F p4
#define T p5

void
eval_draw(void)
{
	if (drawing) {
		push_symbol(NIL);
		return;
	}

	drawing = 1;

	F = cadr(p1);
	T = caddr(p1);

	if (!isusersymbol(T))
		T = symbol(SYMBOL_X);

	save_binding(T);

	setup_trange();
	setup_xrange();
	setup_yrange();

	setup_final();

	draw_count = 0;

	draw_pass1();
	draw_pass2();

	emit_graph();

	restore_binding(T); // restore binding of 2nd arg

	push_symbol(NIL); // draw returns nil

	drawing = 0;
}

void
setup_trange(void)
{
	// default range is (-pi, pi)

	tmin = -M_PI;
	tmax = M_PI;

	p1 = get_binding(lookup("trange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	tmin = pop_double();

	push(p3);
	tmax = pop_double();

	if (tmin == tmax)
		stop("draw: trange is zero");
}

void
setup_xrange(void)
{
	// default range is (-10,10)

	xmin = -10.0;
	xmax = 10.0;

	p1 = get_binding(lookup("xrange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	xmin = pop_double();

	push(p3);
	xmax = pop_double();

	if (xmin == xmax)
		stop("draw: xrange is zero");
}

void
setup_yrange(void)
{
	// default range is (-10,10)

	ymin = -10.0;
	ymax = 10.0;

	p1 = get_binding(lookup("yrange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	ymin = pop_double();

	push(p3);
	ymax = pop_double();

	if (ymin == ymax)
		stop("draw: yrange is zero");
}

void
setup_final(void)
{
	push_double(tmin);
	p1 = pop();
	set_binding(T, p1);

	push(F);
	eval_nonstop();
	p1 = pop();

	if (!istensor(p1)) {
		tmin = xmin;
		tmax = xmax;
	}
}

void
draw_pass1(void)
{
	int i;
	double t;
	for (i = 0; i <= DRAW_WIDTH; i++) {
		t = tmin + (tmax - tmin) * i / DRAW_WIDTH;
		sample(t);
	}
}

void
draw_pass2(void)
{
	int i, j, m, n;
	double dx, dy, t, t1, t2, x1, x2, y1, y2;

	n = draw_count - 1;

	for (i = 0; i < n; i++) {

		t1 = draw_buf[i].t;
		t2 = draw_buf[i + 1].t;

		x1 = draw_buf[i].x;
		x2 = draw_buf[i + 1].x;

		y1 = draw_buf[i].y;
		y2 = draw_buf[i + 1].y;

		if (invisible(x1, y1) && invisible(x2, y2))
			continue;

		dx = x2 - x1;
		dy = y2 - y1;

		m = sqrt(dx * dx + dy * dy);

		for (j = 1; j < m; j++) {
			t = t1 + (double) j / m * (t2 - t1);
			sample(t);
		}
	}
}

void
sample(double t)
{
	double x, y;

	if (draw_count == DRAW_MAX)
		return;

	push_double(t);
	p1 = pop();
	set_binding(T, p1);

	push(F);
	eval_nonstop();
	sfloat();
	p1 = pop();

	if (istensor(p1)) {
		p2 = p1->u.tensor->elem[0];
		p3 = p1->u.tensor->elem[1];
	} else {
		push_double(t);
		p2 = pop();
		p3 = p1;
	}

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	x = pop_double();

	push(p3);
	y = pop_double();

	x = DRAW_WIDTH * (x - xmin) / (xmax - xmin);
	y = DRAW_HEIGHT * (y - ymin) / (ymax - ymin);

	draw_buf[draw_count].x = x;
	draw_buf[draw_count].y = y;
	draw_buf[draw_count].t = t;

	draw_count++;
}

int
invisible(double x, double y)
{
	return x < 0 || x > DRAW_WIDTH || y < 0 || y > DRAW_HEIGHT;
}
