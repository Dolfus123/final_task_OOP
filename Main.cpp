#include <iostream>
#include<Windows.h>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Service
{
private:
	string nameServise;
	int price;
public:
	static int priceVip;
	static double procBonus1;
	static double procBonus2;
	bool type;
	Service(string nameServise, int price, bool type) {
		this->nameServise = nameServise;
		this->price = price;
		this->type = type;
	}

	Service() {
		nameServise = nameServise;
		price = price;
		type = type;
	}

	void setNameServise(string nameServise) {
		this->nameServise = nameServise;
	}

	string getNameServise() {
		return this->nameServise;
	}

	void setPrice(int price) {
		this->price = price;
	}

	int getPrice() {
		return this->price;
	}
	void Print() {
		cout << "название: " << this->getNameServise() << " , стоимость: " << this->getPrice() << endl;
	}

	virtual ~Service() {
	}
};

int Service::priceVip = 500;
double Service::procBonus1 = 1.05;
double Service::procBonus2 = 0.97;

class StandardService : public Service {
public:
	
	StandardService(string nameServise, int price) :Service(nameServise, price, type) {
		type = false;
	}
	StandardService() :Service() {}
	~StandardService() {}
	
};
class VipService : public Service {
public:
	VipService(string nameServise, int price) :Service(nameServise, price, type) {
		type = true;
	}
	VipService() :Service() {}
	~VipService() {}
};

class Client
{
private:
	int id;
	string name;
	int deposit;
	
public:
	bool type = false;
	vector <Service*> ServiceList;
	Client(int id, string name, int deposit, bool type) {
		if (id < 0) {
			this->id = -id;
		}else this->id = id;
		this->name = name;
		this->deposit = deposit;
		this->type = type;
	}

	Client() {
		id = id;
		name = name;
		deposit = deposit;
		type = type;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() {
		return this->name;
	}

	void setDeposit(int deposit) {
		this->deposit = deposit;
	}

	int getDeposit() {
		return this->deposit;
	}
	bool setServiceList(vector <Service*> Services, int i) {
		if (deposit >= Service::priceVip | Services[i]->type != true  /*deposit - Services[i]->getPrice()>0*/)
		{
			if (deposit - Services[i]->getPrice() > 0/*Services[i]->type != 0*/)
			{
				if (Services[i]->type != 0/*deposit>500*/)
				{
					ServiceList.push_back(new VipService(Services[i]->getNameServise(), Services[i]->getPrice()));
					deposit -= (Services[i]->getPrice()* Service::procBonus2);
					cout << "vip " << endl;
				}
				else {
					ServiceList.push_back(new StandardService(Services[i]->getNameServise(), Services[i]->getPrice()));
					if (deposit >= Service::priceVip)
					{
						deposit -= (Services[i]->getPrice() * Service::procBonus2);
					}
					else {
						deposit -= Services[i]->getPrice();
					}
					
					cout << "standart " << endl;
					/*cout << "Услуга доступна только Vip клиентам, если желаете стать Vip клиентом, пополните баланс до 500 рублей " << endl;*/
				}
				
			}
			else {
				cout << "Недостаточно средств на счету " << endl;
				/*ServiceList.push_back(new StandardService(Services[i]->getNameServise(), Services[i]->getPrice()));
				deposit -= Services[i]->getPrice();
				cout << "standart " << endl;*/
			}
		}else cout << "Услуга доступна только Vip клиентам, если желаете стать Vip клиентом, пополните баланс до 500 рублей " << endl;/* cout << "Недостаточно средств на счету " << endl;*/
		if (deposit < Service::priceVip)
		return false;
		else return true;
	}
	
	void setId(int id) {
		if (id < 0) {
			this->id = -id;
		}
		else this->id = id;
	}

	int getId() {
		return this->id;
	}
		
	virtual void info() {
		cout << "Номер клиента: " << id << ", Имя: " << name << ", депозит: "<< deposit <<", статус: обычный" << endl;
		if (ServiceList.size() != NULL)
		{
			cout << "Услуги: " << endl; 
			for ( int i = 0; i < ServiceList.size(); i++)
			{
				ServiceList[i]->Print();
			}
			
		}else cout << "Услуги еще не оказаны " << endl;
		
	}
	
	friend void pushService(vector <Client*>& Clients, int j, vector <Service*> Services, int i);
	friend void pushDeposit(vector <Client*>& Clients, int j, int sum);
	friend bool cmpName(Client*, Client*);
	friend bool cmpPrice(Client*, Client*);
	virtual ~Client() {}
};

class VipClient : public Client {

public:
	VipClient(int id, string name, int deposit) :Client(id, name, deposit, type) {
		type = true;
		
	
	}

	VipClient() :Client() {}
	void info() {
		cout << "Номер клиента: " << this->getId() << ", Имя: " << this->getName() << ", депозит: " << this->getDeposit() << ", статус: vip" << endl;
		if (ServiceList.size() != NULL)
		{
			cout << "Услуги: " << endl;
			for (int i = 0; i < ServiceList.size(); i++)
			{
				ServiceList[i]->Print();
			}
		}
		else cout << "Услуги еще не оказаны " << endl;
	}
	~VipClient() {
	}
};

bool cmpName(Client* p1, Client* p2) {
	if (p1->getName() >= p2->getName())
	{
		return false;
	}
	else {
		return true;
	}
}

bool cmpPrice(Client* p1, Client* p2) {
	if (p1->getDeposit() >= p2->getDeposit())
	{
		return true;
	}
	else {
		return false;
	}
}

void pushService(vector <Client*>& Clients, int j,vector <Service*> Services, int i) {
	
	bool d = Clients[j]->setServiceList(Services, i);
	if (d == false && Clients[j]->type == true)
	{
		cout << "На Вашем счету меньше "<< Service::priceVip << " рублей, Вы будете переведены в статус обычного клиента, если хотите быть Vip клиентом, пожалуйста пополните баланс" << endl;
		Clients.push_back(new Client(Clients[j]->getId(), Clients[j]->getName(), Clients[j]->getDeposit(), false));
		Clients[Clients.size()-1]->ServiceList = Clients[j]->ServiceList;
		Clients.erase(Clients.cbegin() + j);
	}
}

void pushDeposit(vector <Client*>& Clients, int j, int sum){
	if (Clients[j]->type != false)
	{
		sum = sum * Service::procBonus1;
	}
	Clients[j]->setDeposit(Clients[j]->getDeposit()+sum);
	
	if (Clients[j]->getDeposit()> Service::priceVip && Clients[j]->type == false)
	{
		cout << "Поздравляем! На Вашем счету больше " << Service::priceVip << " рублей, Вы будете переведены в статус Vip клиента" << endl;
		Clients.push_back(new VipClient(Clients[j]->getId(), Clients[j]->getName(), Clients[j]->getDeposit()));
		Clients[Clients.size() - 1]->ServiceList = Clients[j]->ServiceList;
		Clients.erase(Clients.cbegin() + j);
	}

}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <Service*> Services;
	Services.push_back(new StandardService("Массаж", 50));
	Services.push_back(new StandardService("Маникур", 40));
	Services.push_back(new StandardService("Пилинг", 20));
	Services.push_back(new VipService("Пилинг в аквариуме", 60));
	Services.push_back(new VipService("Экстра массаж", 80));


	vector <Client*> Clients;
	Clients.push_back(new VipClient(0,"Антон", 800));
	Clients.push_back(new Client(1,"Егор", 120, false));
	Clients.push_back(new VipClient(2,"Анастасия", 500));
	
	pushService(Clients, 1, Services, 2);
	pushService(Clients, 1, Services, 0);
	pushService(Clients, 1, Services, 0);
	pushService(Clients, 2, Services, 2);
	pushService(Clients, 2, Services, 2);
	pushService(Clients, 0, Services, 1);
	pushService(Clients, 0, Services, 0);
	pushService(Clients, 0, Services, 0);
	pushService(Clients, 0, Services, 0);

		
	int menu1, menu2, fExit = 1;
	int tmpType;
	int tmp2;
	int tmp3;
	string tmpName;

	do
	{
		cout << "1. Работа с клиентами" << endl;
		cout << "2. Работа с услугами" << endl;
		
		cin >> menu1;
		switch (menu1)
		{
			// добавить исключения на клавиши
		case 1: {
			cout << "1. Вывод всех клиентов" << endl;
			cout << "2. Добавление клиента" << endl;
			cout << "3. Удаление клиента" << endl;
			cout << "4. Информация по номеру клиента с указанием списка услуг" << endl;
			cout << "5. Пополнение счета клиента (по номеру клиента)" << endl;
			cout << "6. Оказание услуги клиенту (по номеру клиента)" << endl;
			cout << "7. Изменение статуса Клиента (по номеру клиента)" << endl;
			cout << "8. Сортировка клиентов" << endl;
			cout << "9. Клиент, который потратил больше всего средств на услуги" << endl;
			cin >> menu2;
			switch (menu2)
			{
				case 1: {// вывод клиентов
					for (int i = 0; i < Clients.size(); i++)
					{
						Clients[i]->info();
					}

				}break;
				case 2: { //добавление
					cout << "Укажите имя клиента: " << endl;
					cin >> tmpName;
					cout << "Укажите тип клиета(1 - Standart, 2 - Vip): " << endl;
					cin >> tmpType;
					if (tmpType==2)
					{
						Clients.push_back(new VipClient(Clients.size()+1, tmpName, 0));
						cout << "Клиент добавлен " << endl;
					}
					else {
						Clients.push_back(new Client(Clients.size()+1, tmpName, 0, false));
						cout << "Клиент добавлен " << endl;
					}
								
				}break;
				case 3: { //удаление
					cout << "Укажите № клиента: " << endl;
					cin >> tmpType;
					if (tmpType < Clients.size() && tmpType >= 0)
					{
						Clients.erase(Clients.cbegin() + tmpType);
						cout << "Клиент  " << tmpType << "удален" << endl;
					}
					else {
						cout << "По указанному № клиент не найден " << endl;
					}
				}break;
				case 4: {//список услуг
					cout << "Укажите № клиента: " << endl;
					cin >> tmpType;
					Clients[tmpType]->info();
					
				}break;
				case 5: {//пополнение
					cout << "Укажите № клиента: " << endl;
					cin >> tmpType;
					cout << "Укажите сумму пополнения: " << endl;
					cin >> tmp2;
					pushDeposit(Clients, tmpType, tmp2);
					cout << "Зачисление выполнено. На счету: "<< Clients[tmpType]->getDeposit() << endl;
					

				}break;
				case 6: {// оказание услуг
					cout << "Укажите № клиента: " << endl;
					cin >> tmpType;
					cout << "Стандартные услуги: " << endl;
					for (int i = 0; i < Services.size(); i++) {
						if (Services[i]->type == false) {
							cout << i << ") ";
							Services[i]->Print();
						}
					}
					cout << "Премиум услуги: " << endl;
					for (int i = 0; i < Services.size(); i++) {
						if (Services[i]->type == true) {
							cout << i << ") ";
							Services[i]->Print();
						}
					}
					cout << "Укажите № услуги : " << endl;
					cin >> tmp2;
					pushService(Clients, tmpType, Services, tmp2);
					cout << "Услуга оказана " << endl;

				}break;
				case 7: {//изм статус
					cout << "Укажите № клиента: " << endl;
					cin >> tmpType;
					cout << "Укажите статус клиента(1 - Standart, 2 - Vip): " << endl;
					cin >> tmp2;
					if (tmp2==1)
					{
						Clients[tmpType]->type = false;
					}else
					Clients[tmpType]->type = true;
					
				}break;
				case 8: {//сортировка
					cout << "Сортировка: по имени - 1. по дипозиту - 2: " << endl;
					cin >> tmpType;
					if (tmpType==1)
					{
						cout << "Сортировка: " << endl;
						sort(Clients.begin(), Clients.end(), cmpName);
						for (int i = 0; i < Clients.size(); i++)
						{
							Clients[i]->info();
						}
					}
					else {
						cout << "Сортировка: " << endl;
						sort(Clients.begin(), Clients.end(), cmpPrice);
						for (int i = 0; i < Clients.size(); i++)
						{
							Clients[i]->info();
						}
					}

				}break;
				case 9: {//больше потратил
					tmp3 = 0;
					
					for (int i = 0; i < Clients.size(); i++)
					{
						tmp2 = 0;
						for (int j = 0; j < Clients[i]->ServiceList.size(); j++)
						{
							tmp2 += Clients[i]->ServiceList[j]->getPrice();
						}
						
						if (tmp2> tmp3)
						{
							tmp3 = tmp2;
							tmpType = i;
						}
					}
					Clients[tmpType]->info();

				}break;
				
				default:cout << "Неверный запрос " << endl;
				break;
			}
		}break;

		case 2: {
			cout << "1. Вывод списка услуг" << endl;
			cout << "2. Добавление услуги" << endl;
			cout << "3. Удаление услуги (по номеру услуги)" << endl;
			cout << "4. Редактирование услуги (по номеру услуги)" << endl;
			cout << "5. Самая популярная услуга" << endl;
			cout << "6. Услуга, которая приносит больше всего средств" << endl;
			
			cin >> menu2;
			switch (menu2)
			{
			case 1: {//список
				
				cout << "Стандартные услуги: " << endl;
				for (int i = 0; i < Services.size(); i++) {
					if (Services[i]->type == false) {
						cout << i << ") ";
						Services[i]->Print();
					}
				}
				cout << "Премиум услуги: " << endl;
				for (int i = 0; i < Services.size(); i++) {
					if (Services[i]->type == true) {
						cout << i << ") ";
						Services[i]->Print();
					}
				}

			}break;
			case 2: {// добавление
				cout << "Укажите название услуги: " << endl;
				cin >> tmpName;
				cout << "Укажите стоимость услуги: " << endl;
				cin >> tmpType;
				cout << "Укажите тип услуги(1 - Standart, 2 - Vip):  " << endl;
				cin >> tmp2;
				if (tmp2==1){
					Services.push_back(new StandardService(tmpName, tmpType));
					cout << "Услуга успешно добавлена под номером " << Services.size()-1 << endl;
				}
				else{ 
					Services.push_back(new VipService(tmpName, tmpType));
					cout << "Услуга успешно добавлена под номером " << Services.size()-1 << endl;
				}
				
				

			}break;
			case 3: {//удаление по№
				cout << "Укажите № удаляемой услуги :  " << endl;
				cin >> tmp2;
				
				Services.erase(Services.cbegin() + tmp2);
				cout << "Услуга №  "<< tmp2 << " успешно удалена" << endl;

			}break;
			case 4: {//ред по№ 
				// доработать меню редактирования, убрать изменение статуса в метод
				cout << "Укажите № редактируемой услуги :  " << endl;
				cin >> tmp2;
				cout << "Укажите название услуги: " << endl;
				cin >> tmpName;
				cout << "Укажите стоимость услуги: " << endl;
				cin >> tmpType;
				cout << "Укажите тип услуги(1 - Standart, 2 - Vip):  " << endl;
				cin >> tmp3;

				Services[tmp2]->setNameServise(tmpName);
				Services[tmp2]->setPrice(tmpType);
				if (Services[tmp2]->type==false & tmp3 == 2)
				{
					Services.push_back(new VipService(tmpName, tmpType));
					Services[tmp2] = Services[Services.size()-1];
				}
				if (Services[tmp2]->type == true & tmp3 == 1)
				{
					Services.push_back(new StandardService(tmpName, tmpType));
					Services[tmp2] = Services[Services.size()-1];
				}
				cout << "Услуга №  " << tmp2 << " успешно изменена" << endl;
			}break;
			case 5: {// сам попул
				//убрать в метод
				tmp3 = 0;
				tmp2 = 0;
				for (int i = 0; i < Services.size(); i++)
				{
					if (tmp2> tmp3)
					{
						tmp3 = tmp2;
						tmpType = i-1;
					}
					
					tmpName = Services[i]->getNameServise();
					tmp2 = 0;
					for (int j = 0; j < Clients.size(); j++)
					{
						for (int k = 0; k < Clients[j]->ServiceList.size(); k++)
						{
							if (tmpName == Clients[j]->ServiceList[k]->getNameServise())
							{
								tmp2 ++;
							}
						}
					}
				}
				cout << "Самая популярная услуга " << endl;
				Services[tmpType]->Print();
				

			}break;
			case 6: {//сам прибыль
				//убрать в метод
				tmp3 = 0;
				tmp2 = 0;
				int g = 0;
				int testCost = 0;
				for (int i = 0; i < Services.size(); i++)
				{ 
										
					tmpName = Services[i]->getNameServise();
					tmp2 = 0;
					for (int j = 0; j < Clients.size(); j++)
					{
						for (int k = 0; k < Clients[j]->ServiceList.size(); k++)
						{
							if (tmpName == Clients[j]->ServiceList[k]->getNameServise())
							{
								tmp2++;
							}
						}
					}
					if (testCost < tmp2 * Services[i]->getPrice())
					{
						testCost = tmp2 * Services[i]->getPrice();
						tmpType = i;
					}
				}
				cout << "Самая прибыльная услуга " << endl;
				Services[tmpType]->Print();


			}break;
			default:cout << "Неверный запрос " << endl;
				break;
			}


			}break;
		
			default: cout << "Неверный запрос " << endl;
			break;
		}

		system("pause");
		system("cls");

	} while (fExit == 1);

	return 0;
}