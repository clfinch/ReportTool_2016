#include <string>
using namespace std;
class Operator {
	string operatorName;
	int qtyPick;
public:
	string getOperatorName();
	int getQtyPick();
	void setOperatorName(string aName);
	void setQtyPick(int qty);
	Operator(string aName, int aQty); //constructor


};