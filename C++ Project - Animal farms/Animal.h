#ifndef ANIMAL_H_
#define ANIMAL_H_


class Animal {
protected:
	int age;
	int maxAge;

public:
	/* Default constructor */
	Animal() : age(0), maxAge(0){}

	/* Returns the age of the animal */
	int getAge()const;

	/* Returns the price of the animal */
	//int getPrice() const;

	/* Returns the maxAge of the animal */
	int getmaxAge() const;

	/* Increasing age to the animal */
	void increaseAge();

	/* Destructor */
	virtual ~Animal();
};

#endif /* ANIMAL_H_ */
