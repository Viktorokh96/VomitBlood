Пути до настроек препятствий и частей карты пока что лежат в заголовочном файле loader.hpp.

Пример для пробегания по списку тэги-значения:

map<vector<string>, vector<string> >::iterator itmap;
for(itmap = _tagValueM.begin(); itmap!=_tagValueM.end(); itmap++)
{
	vector<string>::iterator itvec;
	vector<string> tags;
	tags = itmap->first;
	//Список (цепочка) тэгов для значений
	cout << "tags: ";
	for(itvec = tags.begin(); itvec != tags.end(); itvec++)
		cout << (*itvec) << " ";
	//Значения
	cout << "values: ";
    for(itvec = itmap->second.begin(); itvec != itmap->second.end(); itvec++)
		cout << (*itvec) << " " << endl;
}