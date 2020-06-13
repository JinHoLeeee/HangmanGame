#include <iostream>
#include <fstream>//ifstream, ofstream 등 파일 입출력을 위한 헤더 파일
#include <string>//string 클래스를 사용하기 위해 포함
#include <time.h>//랜덤으로 숫자를 생성하기 위해 필요
#include <stdlib.h>//랜덤으로 숫자를 생성하기 위해 필요
#include <vector>//Engdic.txt로부터 단어들을 선별하기 위한 공간으로 벡터가 필요-> 벡터 클래스를 사용하기 위해 포함.
using namespace std;

ostream& stars(ostream& outs) {
	outs << "*****";
	return outs;
}

class HangmanGame {
public:
	double score;
	string name;
};

int main() {
	string word;//string 다루는 벡터로부터 단어를 고르기 위함.
	string userword;//화면에 사용자에게 보여줄 단어로, 몇 글자만 '_'로 표시됨.
	int id = 0;//HangmanGame 객체 배열의 번호, 사용자의 이름과 점수 구별에 필요.
	char alpha;//사용자가 정답을 맞추는 과정에 입력하는 알파벳을 받음.
	int wordlength;//word의 길이를 저장.
	int rf = 1;//게임의 반복과 종료를 위해 필요.
	int count;//도전 횟수(1씩 줄어듦.)
	int count2;//도전 횟수(고정적. 불변)
	
	

	ifstream Engdic;
	ofstream rank;
	vector<string> sv;

	HangmanGame *pUser = new HangmanGame[100];

	Engdic.open("C:\\Users\\aaa\\Desktop\\Engdic.txt");
	rank.open("C:\\Users\\aaa\\Desktop\\HangmanRanking2.txt");

	if (!rank) {
		cout << "rank 파일 열 수 없음" << endl;
		return 0;
	}

	if (!Engdic) {
		cout << "Engdic 파일 열 수 없음" << endl;
		return 0;
	}
	for (int i = 0; i < 25143; i++) {
		getline(Engdic, word, '\n');
		sv.push_back(word);
	}
	while (rf != 0) {
		
		cout << "이름을 입력해주세요." << endl;
		cout << "점수가 높으면 명예의 전당에 이름을 올립니다." << endl;
		cin >> pUser[id].name;
		cout << "안녕하세요! " << pUser[id].name << " 님! 총 몇 번 안에 맞추실 건가요?" << endl;
		cout << "10번 이하 >> 점수 1.5배"<<endl;
		
		cout << "성공 횟수를 낮게 잡아 대박을 노려보세요~!!ㅎㅎ" << endl;
		cout << "***참고로 점수 만점은 100점이 아닙니다.***" << endl;
		cout << "최대 도전 횟수는 30회 입니다." << endl;
		cin >> count;
		while (count > 30) {
			cout << "욕심이 많으시군요~!! 최대 도전 횟수는 30회 입니다." << endl;
			cin >> count;
		}
		count2 = count;
		srand((unsigned)time(0));
		int n = rand() % 25143;
		
		word = sv[n];

		while (word.length()==1||word.length()==2) {
			n = rand() % 25143;
			word = sv[n];
		}
		if (word[0] > 64 && word[0] < 91) {
			word[0] = word[0] + 32;
		}
		userword = word;
		wordlength = word.length();
		cout <<"글자 수는 "<< wordlength <<" 입니다."<< endl;
		cout << "단어는 소문자로만 이루어져있습니다. 화이팅!^^" << endl;
		
		for (int z = 0; z < wordlength; z++) {
			userword[z] = '_';
		}
		
		if (wordlength <= 5) {
			for (int z = 0; z < 2; z++) {
				int n2 = rand() % wordlength;
				userword[n2] = word[n2];
			}
		}
		else if (wordlength < 10 && wordlength>5) {
			for (int z = 0; z < 5; z++) {
				int n2 = rand() % wordlength;
				userword[n2] = word[n2];
			}
		}
		else if (wordlength >= 10) {
			for (int z = 0; z < 7; z++) {
				int n2 = rand() % wordlength;
				userword[n2] = word[n2];
			}
		}
		
		
			for (int c=0; c < count2; c++) {
				cout << "남은 횟수 : " << count2-c << " 번" << endl;
				cout << userword << endl;
				cin >> alpha;

				for (int h = 0; h < wordlength; h++) {
					if (word[h] == alpha)
						userword[h] = alpha;

					
				}
				
				if (userword == word)
					break;
				count--;
				
			}
			
			
			if (count2 <= 10) 
				pUser[id].score = (double)count / count2 * 100 * 1.5;

			
			else 
				pUser[id].score = (double)count / count2 * 100;
			
		
			cout << stars << pUser[id].name << " 님의 점수는 " << pUser[id].score << " 입니다." << endl;
		if (pUser[id].score == 0)
		{
			
			cout << stars << "안타깝네요ㅠㅠ" << endl;
			
			
			cout << stars << "정답은 " << word << " 였습니다!" << endl;
			
		}
		cout << "그만하려면 0, 계속하려면 아무 숫자나 눌러주세요.";
		cin >> rf;
		if(rf!=0)
		id++;
	}
	if (id > 0) {
		for (int z = 0; z <= id-1; z++) {
			for (int a = z + 1; a <= id; a++) {
				if (pUser[z].score <= pUser[a].score) {
					double score2 = pUser[z].score;
					pUser[z].score = pUser[a].score;
					pUser[a].score = score2;
					swap(pUser[z].name, pUser[a].name);
				}
			}
		}
	}
	if (id < 4) {


		for (int ran = 0; ran <= id; ran++)
			rank << ran + 1 << " 위는 " << pUser[ran].name << " 이고 " << pUser[ran].score << " 점~!" << endl;
	}
	else if (id > 4) {

		for (int ran = 0; ran <= 4; ran++)
			rank << ran + 1 << " 위는 " << pUser[ran].name << " 이고 " << pUser[ran].score << " 점~!" << endl;
	}
		rank.close();
		Engdic.close();
		delete[]pUser;
		
}