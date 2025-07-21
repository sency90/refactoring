/*
Game Class의 역할이 무엇일까?
이게 애매하다.
심판 역할인가?
Game이 심판이 될 순 없잖아..

실세계를 바탕으로 Game의 역할을 생각해보면,
역할이 있기 보다는 Game내에서 Judge(심판), Player, Questions가 있다고 볼 수 있음.
각각의 객체는 이를 조작하는 Handler가 있다고 보고,
Game이 Start되면, registerJudge(), registerPlayer(), setQuestions()하고..
Game진행은 Judge가 하는게 맞는 것 같음.

강사님은 어떻게 변경했는지 다시 한번 확인 필요
*/
#pragma once
#include "game.h"
#include <queue>
#include <map>
#define interface struct
#define Question std::string

namespace {
	constexpr int INIT_QUESTION_CNT = 50;
	constexpr int LOCATION_CNT = 12;
};

class Questions {
public:
	virtual Question getQuestion() {
		if(questions.empty()) {
			return std::string();
		}
		std::string ret = questions.front();
		questions.pop();
		return ret;
	}
	virtual void push(const Question& question) {
		questions.push(question);
	}
	virtual ~Questions() {}
private:
	std::queue<Question> questions;
};

class PopQuestions: public Questions {};
class ScienceQuestions: public Questions {};
class SportsQuestions: public Questions {};
class RockQuestions: public Questions {};

class QuestionsHandler {
private:
	std::map<std::string, Questions*> questionsDic;
public:
	Question getOneQuestion(const std::string& questionsName) const {
		if(questionsDic.count(questionsName) == 0) {
			return Question();
		}
		return questionsDic.at(questionsName)->getQuestion();
	}
	void setQuestions(const std::string& category) {
		if(category == "Pop") questionsDic["Pop"] = new PopQuestions();
		else if(category == "Science") questionsDic["Science"] = new ScienceQuestions();
		else if(category == "Sports") questionsDic["Sports"] = new SportsQuestions();
		else if(category == "Rock") questionsDic["Rock"] = new RockQuestions();
		else return;

		Questions& questions = *questionsDic.at(category);
		for(int i = 0; i < INIT_QUESTION_CNT; i++) {
			string question = category + " Question " + to_string(i);
			questions.push(question);
		}
	}
	void clear() {
		for(auto& it : questionsDic) {
			if(it.second != nullptr) {
				delete it.second;
			}
		}
		questionsDic.clear();
	}
	virtual ~QuestionsHandler() {
		clear();
	}
};

class Player {
private:
	std::string name;
	int location, coins;
	bool inPenaltyBox;

public:
	Player():location(0), coins(0), inPenaltyBox(false) {}
	Player(const std::string& name):name(name), location(0), coins(0), inPenaltyBox(false) {}

	void goNextLocation(int roll) {
		int nextLocation = (location + roll)%LOCATION_CNT;
		cout << name << "'s new location is " << nextLocation << endl;
		location = nextLocation;
	}
	void goOutPenaltyBox() {
		inPenaltyBox = false;
	}
	void goInPenaltyBox() {
		inPenaltyBox = true;
	}
	void increaseOneCoin() {
		coins++;
		cout << name << " now has " << coins << " Gold Coins." << endl;
	}

	std::string getName() const {
		return name;
	}

	int getCoins() const {
		return coins;
	}

	bool isInPenaltyBox() const {
		return inPenaltyBox;
	}
};

class PlayerHandler {
private:
	int currentOrder;
	std::vector<Player> playerList;
public:
	Player& getCurrentPlayerRef() {
		return playerList[currentOrder];
	}
	void addPlayer(const std::string& name) {
		playerList.emplace_back(name);
	}
	void nextPlayer() {
		int nextOrder = (currentOrder+1)%playerList.size();
		currentOrder = nextOrder;
		cout << playerList[currentOrder].getName() << " is the current player" << endl;
	}
	void correctAnswerAndIncreaseOneCoin() {
		cout << "Answer was correct!!!!" << endl;
		playerList[currentOrder].increaseOneCoin();
	}

	bool isSuccessExitPenaltyBox(int roll) {
		return playerList[currentOrder].isInPenaltyBox() && roll % 2 == 1;
	}
	bool isFailExitPenaltyBox(int roll) {
		return playerList[currentOrder].isInPenaltyBox() && roll % 2 == 0;
	}
};



class GameRefactor: public IGame {
public:
	GameRefactor(): currentPlayer{0}, location{}, coins{} {
		questionsHandler.setQuestions("Pop");
		questionsHandler.setQuestions("Science");
		questionsHandler.setQuestions("Sports");
		questionsHandler.setQuestions("Rock");
	}

	void rolling(int roll) {
		//플레이어 선택
		currentPlayer = getNextPlayer(currentPlayer);

		//주사위 굴리기
		cout << "They have rolled a " << roll << endl;

		//만약 감옥인데, 탈출 실패시
		if(isFailExitPenaltyBox(roll)) {
			cout << players[currentPlayer] << " is not getting out of the penalty box" << endl;
			return;
		}

		//만약 감옥인데, 탈출 성공시
		if(isSuccessExitPenaltyBox(roll)) {
			inPenaltyBox[currentPlayer] = false;
			cout << players[currentPlayer] << " is getting out of the penalty box" << endl;
		}

		//주사위 눈금만큼 이동
		location[currentPlayer] = getNextLocation(location[currentPlayer], roll);

		//이동한 곳에서 퀴즈 풀기
		askQuestion();
	}

	bool correctAnswerQuizAndReturnIsContinueGame() { //정답
		//감옥에서는 퀴즈를 풀 수가 없음.
		if(inPenaltyBox[currentPlayer]) {
			return true;
		}

		//정답
		cout << "Answer was correct!!!!" << endl;

		//코인 UP
		coins[currentPlayer]++;
		cout << players[currentPlayer] << " now has "
			<< coins[currentPlayer] << " Gold Coins." << endl;

		return isContinueGameOrNot();
	}

	bool wrongAnswerQuizAndReturnIsContinueGame() { //틀렸음

		//감옥이면 퀴즈 안풀었음
		if(inPenaltyBox[currentPlayer]) {
			return CONTINUE_GAME;
		}

		//오답, 감옥간다.
		cout << "Question was incorrectly answered" << endl;
		cout << players[currentPlayer] + " was sent to the penalty box" << endl;

		inPenaltyBox[currentPlayer] = true;
		return CONTINUE_GAME;
	}

	bool isPlayable() {
		return (howManyPlayers() >= 2);
	}

	bool add(string playerName) {
		currentPlayer = -1;

		players.push_back(playerName);

		int playerIndex = howManyPlayers() - 1;
		location[playerIndex] = 0;
		coins[playerIndex] = 0;
		inPenaltyBox[playerIndex] = false;

		cout << playerName << " was added" << endl;
		cout << "They are player number " << players.size() << endl;
		return SUCCESS_ADD_PLAYER;
	}

	int howManyPlayers() {
		return (int)players.size();
	}

private:
	bool isSuccessExitPenaltyBox(int roll) {
		return inPenaltyBox[currentPlayer] && roll % 2 == 1;
	}

	bool isFailExitPenaltyBox(int roll) {
		return inPenaltyBox[currentPlayer] && roll % 2 == 0;
	}
	int getNextLocation(int currentPlace, int roll) {
		int nextLocation = currentPlace + roll;
		if(nextLocation >= LOCATION_CNT) nextLocation -= LOCATION_CNT;

		cout << players[currentPlayer] << "'s new location is " << nextLocation << endl;
		return nextLocation;
	}

	int getNextPlayer(int currentPlayer) {
		int nextPlayer = currentPlayer + 1;
		if(nextPlayer == players.size()) nextPlayer = 0;

		cout << players[nextPlayer] << " is the current player" << endl;
		return nextPlayer;
	}

	void askQuestion() {
		string category = currentCategory();
		cout << "The category is " << category << endl;
		cout << questionsHandler.getOneQuestion(category) << endl;
	}

	string currentCategory() {
		if(location[currentPlayer] % 4 == 0) return "Pop";
		if(location[currentPlayer] % 4 == 1) return "Science";
		if(location[currentPlayer] % 4 == 2) return "Sports";
		if(location[currentPlayer] % 4 == 3) return "Rock";
		return "";
	}

	bool isContinueGameOrNot() {
		bool isFinishGame = (coins[currentPlayer] == 6);
		return !isFinishGame;
	}

private:
	const bool CONTINUE_GAME = true;
	const bool SUCCESS_ADD_PLAYER = true;

	vector<string> players;

	int location[6];
	int coins[6];

	bool inPenaltyBox[6];
	QuestionsHandler questionsHandler;

	//list<string> popQuestions;
	//list<string> scienceQuestions;
	//list<string> sportsQuestions;
	//list<string> rockQuestions;

	int currentPlayer;
};