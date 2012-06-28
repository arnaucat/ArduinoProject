#ifndef User_h
#define User_h

class User{
public:
    User(int id,int passwd);
    int getId();
    bool rightPassword(int passwd);
private:
    int id; //id del usuari
    int passwd; //contrassenya del usuari
};

#endif
