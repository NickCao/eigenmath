void
eval_test(struct atom *p1)
{
	struct atom *p2;
	p1 = cdr(p1);
	while (iscons(p1)) {
		if (!iscons(cdr(p1))) {
			push(car(p1)); // default case
			eval();
			return;
		}
		push(car(p1));
		evalp();
		p2 = pop();
		if (!iszero(p2)) {
			push(cadr(p1));
			eval();
			return;
		}
		p1 = cddr(p1);
	}
	push_symbol(NIL);
}

void
eval_check(struct atom *p1)
{
	push(cadr(p1));
	evalp();
	p1 = pop();
	if (iszero(p1))
		stopf("check");
	push_symbol(NIL); // no result is printed
}

void
eval_testeq(struct atom *p1)
{
	struct atom *p2, *p3;

	push(cadr(p1));
	eval();

	push(caddr(p1));
	eval();

	p2 = pop();
	p1 = pop();

	// null tensors are equal no matter the dimensions

	if (iszero(p1) && iszero(p2)) {
		push_integer(1);
		return;
	}

	// shortcut for trivial equality

	if (equal(p1, p2)) {
		push_integer(1);
		return;
	}

	// otherwise subtract and simplify

	if (!istensor(p1) && !istensor(p2)) {
		if (!iscons(p1) && !iscons(p2)) {
			push_integer(0); // p1 and p2 are numbers, symbols, or strings
			return;
		}
		push(p1);
		push(p2);
		subtract();
		simplify();
		p1 = pop();
		if (iszero(p1))
			push_integer(1);
		else
			push_integer(0);
		return;
	}

	if (istensor(p1) && istensor(p2)) {
		if (!compatible_dimensions(p1, p2)) {
			push_integer(0);
			return;
		}
		push(p1);
		push(p2);
		subtract();
		simplify();
		p1 = pop();
		if (iszero(p1))
			push_integer(1);
		else
			push_integer(0);
		return;
	}

	if (istensor(p2)) {
		// swap p1 and p2
		p3 = p1;
		p1 = p2;
		p2 = p3;
	}

	if (!iszero(p2)) {
		push_integer(0); // tensor not equal scalar
		return;
	}

	push(p1);
	simplify();
	p1 = pop();

	if (iszero(p1))
		push_integer(1);
	else
		push_integer(0);
}

int
cross_expr(struct atom *p)
{
	if (car(p) == symbol(ADD)) {
		p = cdr(p);
		while (iscons(p)) {
			if (cross_term(car(p)))
				return 1;
			p = cdr(p);
		}
		return 0;
	}

	return cross_term(p);
}

int
cross_term(struct atom *p)
{
	if (car(p) == symbol(MULTIPLY)) {
		p = cdr(p);
		while (iscons(p)) {
			if (cross_factor(car(p)))
				return 1;
			p = cdr(p);
		}
		return 0;
	}

	return cross_factor(p);
}

int
cross_factor(struct atom *p)
{
	if (isrational(p)) {
		if (MEQUAL(p->u.q.b, 1))
			return 0;
		push_bignum(MPLUS, mcopy(p->u.q.b), mint(1));
		return 1;
	}

	if (car(p) == symbol(POWER) && !isminusone(cadr(p)) && isnegativeterm(caddr(p))) {
		if (isminusone(caddr(p)))
			push(cadr(p));
		else {
			push_symbol(POWER);
			push(cadr(p));
			push(caddr(p));
			negate();
			list(3);
		}
		return 1;
	}

	return 0;
}

void
cancel_factor(void)
{
	int h;
	struct atom *p1, *p2;

	p2 = pop();
	p1 = pop();

	if (car(p2) == symbol(ADD)) {
		h = tos;
		p2 = cdr(p2);
		while (iscons(p2)) {
			push(p1);
			push(car(p2));
			multiply();
			p2 = cdr(p2);
		}
		add_terms(tos - h);
	} else {
		push(p1);
		push(p2);
		multiply();
	}
}

void
eval_testge(struct atom *p1)
{
	if (cmp_args(p1) >= 0)
		push_integer(1);
	else
		push_integer(0);
}

void
eval_testgt(struct atom *p1)
{
	if (cmp_args(p1) > 0)
		push_integer(1);
	else
		push_integer(0);
}

void
eval_testle(struct atom *p1)
{
	if (cmp_args(p1) <= 0)
		push_integer(1);
	else
		push_integer(0);
}

void
eval_testlt(struct atom *p1)
{
	if (cmp_args(p1) < 0)
		push_integer(1);
	else
		push_integer(0);
}

void
eval_not(struct atom *p1)
{
	push(cadr(p1));
	evalp();
	p1 = pop();
	if (iszero(p1))
		push_integer(1);
	else
		push_integer(0);
}

void
eval_and(struct atom *p1)
{
	struct atom *p2;
	p1 = cdr(p1);
	while (iscons(p1)) {
		push(car(p1));
		evalp();
		p2 = pop();
		if (iszero(p2)) {
			push_integer(0);
			return;
		}
		p1 = cdr(p1);
	}
	push_integer(1);
}

void
eval_or(struct atom *p1)
{
	struct atom *p2;
	p1 = cdr(p1);
	while (iscons(p1)) {
		push(car(p1));
		evalp();
		p2 = pop();
		if (!iszero(p2)) {
			push_integer(1);
			return;
		}
		p1 = cdr(p1);
	}
	push_integer(0);
}

int
cmp_args(struct atom *p1)
{
	struct atom *p2;

	push(cadr(p1));
	eval();
	p2 = pop();
	push(p2);
	if (!isnum(p2))
		floatfunc();

	push(caddr(p1));
	eval();
	p2 = pop();
	push(p2);
	if (!isnum(p2))
		floatfunc();

	return cmpfunc();
}

// like eval() except '=' is evaluated as '=='

void
evalp(void)
{
	struct atom *p1;
	p1 = pop();
	if (car(p1) == symbol(SETQ))
		eval_testeq(p1);
	else {
		push(p1);
		eval();
	}
}
