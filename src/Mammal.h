/*
 * Mammal.h
 *
 *  Created on: Feb 22, 2021
 *      Author: 1729264_snhu
 */

#ifndef MAMMAL_H_
#define MAMMAL_H_
#include <string>
#include "Animal.h"


class Mammal: public Animal {
	std::string m_subtype;
	int m_eggs;
	int m_nurse;



public:
	Mammal();
	virtual ~Mammal();

	int getEggs() const {
		return m_eggs;
	}

	void setEggs(int eggs) {
		m_eggs = eggs;
	}

	int getNurse() const {
		return m_nurse;
	}

	void setNurse(int nurse) {
		m_nurse = nurse;
	}

	const std::string& getSubtype() const {
		return m_subtype;
	}

	void setSubtype(const std::string& subtype) {
		m_subtype = subtype;
	}
};

#endif /* MAMMAL_H_ */
