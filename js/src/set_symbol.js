function
set_symbol(p, b, u)
{
	if (!isusersymbol(p))
		stopf("symbol error");
	if (journaling)
		journal.push(p, get_binding(p), get_usrfunc(p));
	binding[p.printname] = b;
	usrfunc[p.printname] = u;
}
