#ifndef SALS_ITEM_H
#define SALS_ITEM_H

#include <iostream>
#include <string>

class Sales_item {
	friend std::istream& operator >>(std::istream&, Sales_item&);

	friend std::ostream& operator <<(std::ostream&, const Sales_item&);

	friend bool operator <(const Sales_item&, const Sales_item&);

	friend bool operator ==(const Sales_item&, const Sales_item&);
	
public:
	Sales_item() = default;

	Sales_item(const std::string& bookNo):bookNo(bookNo) {}

	Sales_item(std::istream& is) {is >> *this;}

public:
	Sales_item& operator+=(const Sales_item&);

	std::string isbn() const {return bookNo;}

	double avg_price() const;

private:
	std::string bookNo;

	unsigned units_sold = 0;

	double revenue = 0.0;
};

std::istream& operator >>(std::istream &in, Sales_item &item)
{
	double price;
	in >> item.bookNo >> item.units_sold >> price;
	if (in) {
		item.revenue = item.units_sold * price;
	} else {
		item = Sales_item();
	}
	return in;
}

std::ostream& operator <<(std::ostream &out, const Sales_item& item)
{
	if (out) {
		out << item.isbn() << "  " << item.units_sold << "	" << item.revenue << "	" << item.avg_price();
	}
	return out;
}

double Sales_item::avg_price() const
{
	if (units_sold) {
		return revenue / units_sold;
	} else {
		return 0.0;
	}
}

bool operator <(const Sales_item& item1, const Sales_item& item2)
{
	return item1.revenue < item2.revenue;
}

bool operator ==(const Sales_item& item1, const Sales_item& item2)
{
	return item1.revenue == item2.revenue &&
		   item1.units_sold == item2.units_sold &&
		   item1.isbn() == item2.isbn();
}

Sales_item& Sales_item::operator+=(const Sales_item& item)
{
	units_sold += item.units_sold; 
	revenue += item.revenue;
	return *this;
}

Sales_item operator +(const Sales_item& item01, const Sales_item& item02)
{
	Sales_item retitem(item02);
	retitem += item01;
	return retitem;
}	
#endif //SALS_ITEM_H

