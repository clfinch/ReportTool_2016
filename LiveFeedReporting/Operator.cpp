#include "Operator.h"

Operator::Operator(string aOperatorName, int aqtyPick){
	setOperatorName(aOperatorName);
	setQtyPick(aqtyPick);
}// end constructor

string::getOperatorName(){return operatorName;}

int::getQtyPick(){return qtyPick;}

void::setOperatorName(string aName){operatorName = aName;}

void::setQtyPick(int aQty){qtyPick = aQty;}