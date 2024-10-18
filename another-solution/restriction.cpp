#include "restriction.h"

int Restriction::getMyLetterPos() const {
    return _myLetterPos;
}

void Restriction::setMyLetterPos(const int myLetterPos) {
    _myLetterPos = myLetterPos;
}

int Restriction::getIdOtherWord() const {
    return _idOtherWord;
}

void Restriction::setIdOtherWord(const int idOtherWord) {
    _idOtherWord = idOtherWord;
}

int Restriction::getOtherWordLetterPos() const {
    return _otherWordLetterPos;
}

void Restriction::setOtherWordLetterPos(const int otherWordLetterPos) {
    _otherWordLetterPos = otherWordLetterPos;
}

std::ostream& operator<<(std::ostream& os, Restriction* s) {
    os << "[MY_LETTER] " << s->getMyLetterPos() << " [ID_OTHER_WORD] " << s->getIdOtherWord() 
        << " [OTHER_WORD_LETTER_POS] " << s->getOtherWordLetterPos();
    return os;
}

std::ostream& operator << (std::ostream& os, std::vector<Restriction*> v) 
{
    os << "[";
    for (typename std::vector<Restriction*>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        os << *ii << ", ";
    }
    os << "]";
    return os;
}