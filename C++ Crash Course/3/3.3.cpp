#include <cstdio>
#include <cstring>

struct Element
{
	Element* next{};
	Element* previous{};
		
	void insert_before(Element* new_element)
	{
		new_element->next = this;
		new_element->previous = this->previous;
		if(this->previous->next)
			this->previous->next = new_element;
		this->previous = new_element;
	}

	void insert_after(Element* new_element)
	{
		new_element->next = this->next;
		new_element->previous = this;
		if(this->next)
			this->next->previous = new_element;
		this->next = new_element;
	}

	char prefix[3];
	unsigned short operating_number;
};

int main()
{
	Element trooper1, trooper2, trooper3;
	strcpy(trooper1.prefix, "TK");
	trooper1.operating_number = 421;
	trooper1.insert_after(&trooper2);
	
	strcpy(trooper2.prefix, "FN");
	trooper2.operating_number = 2187;
	trooper2.insert_after(&trooper3);
	
	strcpy(trooper3.prefix, "LS");
	trooper3.operating_number = 5;
	
	for(Element *cursor = &trooper1; cursor; cursor = cursor->next)
	{
		printf("stormtrooper: %s-%d\n", cursor->prefix, cursor->operating_number);
	}
	printf("go back:\n");
	for(Element *cursor = &trooper3; cursor; cursor=cursor->previous)
	{
		printf("stormtrooper: %s-%d\n", cursor->prefix, cursor->operating_number);
	}
	return 0;
}


