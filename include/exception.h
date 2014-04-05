/*
 * exception.h
 *
 *  Created on: Apr 2, 2014
 *      Author: vlad
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <stdexcept>
#include <string>

// exception class

namespace qpp
{

class Exception: public std::exception
{
public:
	enum class Type // exception types
	{
		UNKNOWN_EXCEPTION = 0,
		ZERO_SIZE,
		MATRIX_NOT_SQUARE,
		MATRIX_NOT_CVECTOR,
		MATRIX_NOT_RVECTOR,
		MATRIX_NOT_VECTOR,
		DIMS_INVALID,
		DIMS_NOT_EQUAL,
		DIMS_MISMATCH_MATRIX,
		SUBSYS_MISMATCH_DIMS,
		PERM_MISMATCH_DIMS,
		NOT_QUBIT_GATE,
		NOT_QUBIT_SUBSYS,
		OUT_OF_RANGE,
		UNDEFINED_TYPE,
		CUSTOM_EXCEPTION
	};

	Exception(const std::string & where, const Type& type) :
			_where(where), _msg(), _type(type), _custom()
	{
		_construct_exception_msg();
	}

	Exception(const std::string & where, const std::string & custom) :
			_where(where), _msg(), _type(Type::CUSTOM_EXCEPTION), _custom(
					custom)
	{
		_construct_exception_msg();
		_msg += custom; // add the custom message at the end
	}

	virtual const char* what() const noexcept override
	{
		return _msg.c_str();
	}

	virtual ~Exception() noexcept
	{
	}
private:
	std::string _where, _msg;
	Type _type;
	std::string _custom;

	std::string _construct_exception_msg()
	{
		_msg += "IN ";
		_msg += _where;
		_msg += ": ";

		switch (_type)
		{
		case Type::UNKNOWN_EXCEPTION:
			_msg += "UNKNOWN EXCEPTION!";
			break;
		case Type::ZERO_SIZE:
			_msg += "Object has zero size!";
			break;
		case Type::MATRIX_NOT_SQUARE:
			_msg += "Matrix is not square!";
			break;
		case Type::MATRIX_NOT_CVECTOR:
			_msg += "Matrix is not a column vector!";
			break;
		case Type::MATRIX_NOT_RVECTOR:
			_msg += "Matrix is not a row vector!";
			break;
		case Type::MATRIX_NOT_VECTOR:
			_msg += "Matrix is not a vector!";
			break;
		case Type::DIMS_INVALID:
			_msg += "Invalid dimension(s)!";
			break;
		case Type::DIMS_NOT_EQUAL:
			_msg += "Dimensions not equal!";
			break;
		case Type::DIMS_MISMATCH_MATRIX:
			_msg += "Dimensions mismatch matrix size!";
			break;
		case Type::SUBSYS_MISMATCH_DIMS:
			_msg += "Subsystems mismatch dimensions!";
			break;
		case Type::PERM_MISMATCH_DIMS:
			_msg += "Permutation mismatch dimensions!";
			break;
		case Type::NOT_QUBIT_GATE:
			_msg += "Matrix is not a qubit gate!";
			break;
		case Type::NOT_QUBIT_SUBSYS:
			_msg += "Subsystems are not qubits!";
			break;
		case Type::OUT_OF_RANGE:
			_msg += "Parameter out of range!";
			break;
		case Type::UNDEFINED_TYPE:
			_msg += "Not defined for this type!";
			break;
		case Type::CUSTOM_EXCEPTION:
			return _msg += "CUSTOM EXCEPTION ";
			break;
		}
		return _msg;
	}
};

} /* namespace qpp */

#endif /* EXCEPTION_H_ */
