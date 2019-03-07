#include "stdafx.h"
#include "exp.h"

/*sales_data & sales_data::operator+=(const sales_data &r)
{
	if (isbn != r.isbn)
		throw isbn_mismatch("wrong isbns", isbn, r.isbn);
	units_sold += r.units_sold;
	revenue += r.revenue;
	return *this;
}
*/
//18.27
/*void MI::foo(double cval)
{
	int dval= Base1::dval + Derived::dval;
	Base2::fval = MI::dvec.back();
	Derived::sval[0] = Base1::cval;
}
*/
Basic& Basic::operator=(const Basic &b)
{
	a = b.a;
	return *this;
}
