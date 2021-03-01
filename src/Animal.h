/*
 * Animal.h
 *
 *  Created on: Feb 21, 2021
 *      Author: 1729264_snhu
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_
#include <string>


class Animal {
	std::string m_trackNum;
	std::string m_name;
	std::string m_type;

public:
	Animal();
	virtual ~Animal();
	const std::string& getName() const;
	void setName(const std::string& name);
	const std::string& getTrackNum() const;
	void setTrackNum(const std::string& trackNum);
	const std::string& getType() const;
	void setType(const std::string& type);
};

#endif /* ANIMAL_H_ */
