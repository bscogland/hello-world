/*
 * Animal.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: 1729264_snhu
 */

#include "Animal.h"

Animal::Animal() {
	// TODO Auto-generated constructor stub

}

const std::string& Animal::getName() const {
	return m_name;
}

void Animal::setName(const std::string& name) {
	m_name = name;
}

const std::string& Animal::getTrackNum() const {
	return m_trackNum;
}

void Animal::setTrackNum(const std::string& trackNum) {
	m_trackNum = trackNum;
}

const std::string& Animal::getType() const {
	return m_type;
}

void Animal::setType(const std::string& type) {
	m_type = type;
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}

