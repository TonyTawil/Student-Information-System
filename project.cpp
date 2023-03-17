#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

struct student;

struct enrolledStudent {
    student* studentReference;
    enrolledStudent* next;
};

struct Time {
    string day;
    int startHour, endHour, startMin, endMin;
};

struct course {
    int courseID, courseCapacity, attendeeNb;
    string courseName, instructorName;
    Time timeSchedule;
    enrolledStudent* attendees;
    course* next;
    course* previous;
};

struct enrolledCourse {
    course* courseReference;
    int att = 1;
    double grade = 0;
    enrolledCourse* next;
    enrolledCourse* previous;
};

struct universityCourseList {
    course* head, * tail;
};

struct enrolledCourseList {
    enrolledCourse* head, * tail;
};

struct student {
    int studentID = 0, courseNb;
    string firstName, lastName, emailAddress, password;
    enrolledCourseList enrolledCourse;
    student* next;
};


struct instructor {
    int instroctorID;
    string name;
    string emailAddress;
    string password;
    instructor* next;
    instructor* previous;
};

struct instructorList {
    instructor* head;
    instructor* tail;
};

void DrawLines(int n, char symbol) {
    for (int i = 0; i < n; i++) {
        cout << symbol;
    }
    cout << endl;
}

bool IsEmpty(student* head)
{
    return (head == NULL);
}

bool isEmptyDoubly(universityCourseList list)
{
    return(list.head == NULL || list.tail == NULL);
}

//void PrintList(student* head)
//{
//    student* cur;
//    if (IsEmpty(head))
//    {
//        cout << "The list is empty" << endl;
//        return;
//    }
//    cout << "The list is:" << endl;
//    cur = head;
//
//    while (cur != NULL)
//    {
//        cout << cur->studentID << " ";
//        cout << cur->firstName << " ";
//        cout << cur->lastName << " ";
//        cout << cur->emailAddress << " ";
//        cout << cur->courseNb << " ";
//
//        enrolledCourse* curr = new enrolledCourse;
//        curr = cur->enrolledCourse.head;
//        while (curr != NULL)
//        {
//            cout << curr->courseReference->courseID;
//            curr = curr->next;
//        }
//
//        cout << endl;
//        cur = cur->next;
//    }
//    cout << endl;
//
//}

void PrintListH2R(universityCourseList l)
{
    course* cur = l.head;
    if (isEmptyDoubly(l)) {
        cout << "There are no courses" << endl;
        return;
    }
    cout << "The courses are:" << endl;
    while (cur != NULL) {
        cout << cur->courseID << " " << cur->courseCapacity << " " << cur->courseName << " " << cur->instructorName << " " << cur->timeSchedule.day << " " << cur->timeSchedule.startHour << ":";
        if (cur->timeSchedule.startMin < 10)
            cout << "0" << cur->timeSchedule.startMin << " ";
        else
            cout << cur->timeSchedule.startMin << " ";

        cout << cur->timeSchedule.endHour << ":";

        if (cur->timeSchedule.endMin < 10)
            cout << "0" << cur->timeSchedule.endMin << " ";
        else
            cout << cur->timeSchedule.endMin;

        cout << endl;
        cur = cur->next;
    }
    cout << endl;
}

student* InsertAtQueue(student* head, int ID, int courseNb, string fname, string lname, string mail, string password, enrolledCourseList* l)
{
    student* tmp, * cur;
    tmp = new student;

    tmp->studentID = ID;
    tmp->courseNb = courseNb;
    tmp->firstName = fname;
    tmp->lastName = lname;
    tmp->emailAddress = mail;
    tmp->password = password;
    tmp->enrolledCourse = *l;
    tmp->next = NULL;
    //If the list is empty
    if (head == NULL)
    {
        head = tmp;
        return head;
    }
    //Search for the queue of list
    cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    //insertion
    cur->next = tmp;

    return head;
}

course* insertAtQueueCourses(universityCourseList* list, int ID, int capacity, int attendeeNb, string courseName, string instructorName, Time T)
{
    course* tmp;
    tmp = new course;

    tmp->courseID = ID;
    tmp->courseCapacity = capacity;
    tmp->attendeeNb = attendeeNb;
    tmp->courseName = courseName;
    tmp->instructorName = instructorName;
    tmp->timeSchedule = T;


    tmp->next = NULL;
    tmp->previous = NULL;

    if (isEmptyDoubly(*list))
    {
        list->head = tmp;
        list->tail = tmp;
    }
    else
    {
        tmp->previous = list->tail;
        list->tail->next = tmp;
        list->tail = tmp;
    }
    return list->head;
}

instructor* insertAtQueueInstructors(instructorList*& list, int ID, string instructorName, string email, string password)
{
    instructor* tmp;
    tmp = new instructor;

    tmp->instroctorID = ID;
    tmp->name = instructorName;
    tmp->emailAddress = email;
    tmp->password = password;
    //cout << tmp->emailAddress << " " << endl;

    tmp->next = NULL;
    tmp->previous = NULL;

    if (list->head == NULL || list->tail == NULL)
    {
        list->head = tmp;
        list->tail = tmp;
    }
    else
    {
        tmp->previous = list->tail;
        list->tail->next = tmp;
        list->tail = tmp;
    }
    return list->head;
}

int countCourses(string s)
{
    int i, c = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '\t')
            c++;
    }
    return c + 1;
}

void fillEnrolledCourse(enrolledCourseList& l, course* c)
{
    enrolledCourse* tmp = new enrolledCourse;

    tmp->courseReference = c;
    tmp->next = NULL;
    tmp->previous = NULL;

    if (l.head == NULL || l.tail == NULL)
    {
        l.head = tmp;
        l.tail = tmp;
        return;
    }
    else
    {
        tmp->previous = l.tail;
        l.tail->next = tmp;
        l.tail = tmp;
    }
}

void fillStudents(student*& head, universityCourseList* courseList)
{
    student* curr = new student;
    curr = head;

    course c;

    string ID, firstName, lastName, email, password, courseNumber, courses;

    ifstream students;
    students.open("students.txt");
    while (getline(getline(getline(getline(getline(getline(getline(students, ID, '\t'), firstName, '\t'), lastName, '\t'), email, '\t'), password, '\t'), courseNumber, '\t'), courses))
    {
        enrolledCourseList list;
        list.head = NULL;
        list.tail = NULL;


        istringstream iss(courses);

        for (int i = 0; i < stoi(courseNumber); i++)
        {
            course* cur;
            cur = courseList->head;
            string courseA;
            getline(iss, courseA, '\t');
            while (cur != NULL)
            {
                if (stoi(courseA) == cur->courseID)
                {
                    fillEnrolledCourse(list, cur);
                    //cout<<cur->courseName;
                    break;
                }
                cur = cur->next;
            }
        }
        //cout << list.head->courseReference->courseName;
        head = InsertAtQueue(head, stoi(ID), stoi(courseNumber), firstName, lastName, email, password, &list);

    }
    students.close();
}

void fillCourses(universityCourseList*& courseList)
{
    course* c = new course;
    c = courseList->head;
    c = courseList->tail;

    string ID, capacity, attendeeNb, courseName, instructorName, day, startHour, startMin, endHour, endMin;

    ifstream courses;
    courses.open("courses.txt");

    while (getline(getline(getline(getline(getline(getline(getline(getline(getline(getline(courses, ID, '\t'), capacity, '\t'), attendeeNb, '\t'), courseName, '\t'), instructorName, '\t'), day, '\t'), startHour, ':'), startMin, '\t'), endHour, ':'), endMin))
    {
        Time T;
        T.day = day;
        T.startHour = stoi(startHour);
        T.endHour = stoi(endHour);
        T.startMin = stoi(startMin);
        T.endMin = stoi(endMin);

        courseList->head = insertAtQueueCourses(courseList, stoi(ID), stoi(capacity), stoi(attendeeNb), courseName, instructorName, T);
    }
}


void fillInstructor(instructorList*& EL)
{
    instructor* e = new instructor;
    e = EL->head;
    e = EL->tail;

    string ID, instructorName, email, password;

    ifstream instructors;
    instructors.open("instructors.txt");

    while (getline(getline(getline(getline(instructors, ID, '\t'), instructorName, '\t'), email, '\t'), password))
    {
        EL->head = insertAtQueueInstructors(EL, stoi(ID), instructorName, email, password);

    }
}

//void insertAtQueueES(enrolledStudent*& es, student* s)
//{
//    enrolledStudent* tmp = new enrolledStudent;
//
//    tmp->studentReference = s;
//    tmp->next = NULL;
//
//    //If the list is empty
//    if (es == NULL)
//    {
//        es = tmp;
//        return;
//    }
//    //Search for the queue of list
//    enrolledStudent* cur = es;
//    while (cur->next != NULL)
//    {
//        cur = cur->next;
//    }
//    //insertion
//    cur = tmp;
//}

void fillAttendees(student* head, universityCourseList*& l)
{
    course* curc = l->head;


    while (curc != NULL)
    {
        curc->attendees = 0;
        enrolledStudent* cures = curc->attendees;


        student* curs;
        curs = head;
        while (curs != NULL)
        {
            enrolledCourse* curec = curs->enrolledCourse.head;
            while (curec != NULL)
            {
                if (curc->courseID == curec->courseReference->courseID)
                {
                    curc->attendees++;
                    enrolledStudent* tempes = new enrolledStudent;
                    if (tempes == NULL)
                        exit(1);
                    tempes->next = NULL;
                    tempes->studentReference = curs;
                    tempes->next = curc->attendees;
                    curc->attendees = tempes;

                }
                curec = curec->next;
            }
            curs = curs->next;
        }
        curc = curc->next;
    }
}

bool verification_password(string password) {
    int hasDigit = 0, hasAlpha = 0, hasSpecial_characters = 0;
    for (int i = 0;i < password.length();i++) {
        if (isdigit(password[i]))
            hasDigit++;
        else if (isalpha(password[i]))
            hasAlpha++;
        else
            hasSpecial_characters++;
    }
    if (password.length() < 8) {
        cout << "The password should contain at least 8 characters: " << endl;
        return false;
    }
    if (hasAlpha == 0 || hasDigit == 0 || hasSpecial_characters == 0) {
        cout << "The password should contain at least 1 letter, 1 number and 1 special character: " << endl;
        return false;
    }

    return true;

}

bool excistanceOfEmail(student* s, string email)
{
    student* cur;
    cur = s;
    while (cur != NULL)
    {
        if (cur->emailAddress == email)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

int login(student* s)
{
    string email;
    cout << "Enter your email: ";
    getline(cin, email);
    while (excistanceOfEmail(s, email) == false) {
        cout << "This email does not exist: Renter it ";
        getline(cin, email);
    }

    int a, id = 0;
    a = 0;
    student* cur;
    cur = s;
    string password;
    while (cur != NULL)
    {
        if (cur->emailAddress == email)
        {
            id = cur->studentID;
            cout << "Please enter you password now: ";
            getline(cin, password);

            while (password != cur->password) {
                cout << "Incorrect password: Renter: ";
                getline(cin, password);
            }
        }

        cur = cur->next;
    }
    return id;
}

bool excistanceOfEmailInstructor(instructorList* e, string email)
{
    instructor* cur;
    cur = e->head;
    while (cur != NULL)
    {

        if (cur->emailAddress == email)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

string loginInstructor(instructorList* e)
{
    string emaill;
    cout << "Enter your email: ";
    getline(cin, emaill);
    while (excistanceOfEmailInstructor(e, emaill) == false) {
        cout << "This email does not exist renter it: ";
        getline(cin, emaill);
    }

    int a;
    string n = "";
    a = 0;
    instructor* cur;
    cur = e->head;
    string password;
    while (cur != NULL)
    {
        if (cur->emailAddress == emaill)
        {
            n = cur->name;
            cout << "Please enter you password now: ";
            getline(cin, password);

            while (password != cur->password) {
                cout << "Incorrect password: Renter: ";
                getline(cin, password);
            }
        }

        cur = cur->next;
    }
    return n;
}

student* InsertAtQueue2(student* head, int ID, int courseNb, string fname, string lname, string mail)
{
    student* tmp, * cur;
    tmp = new student;

    tmp->studentID = ID;
    tmp->courseNb = courseNb;
    tmp->firstName = fname;
    tmp->lastName = lname;
    tmp->emailAddress = mail;
    tmp->next = NULL;
    //If the list is empty
    if (head == NULL)
    {
        head = tmp;
        return head;
    }
    //Search for the queue of list
    cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    //insertion
    cur->next = tmp;

    return head;
}

//int signup(student* s)
//{
//    int ID;
//    string firstName, lastName, email;
//    cout << "Enter your first name: ";
//    getline(cin, firstName);
//    cout << "Enter your last name: ";
//    getline(cin, lastName);
//    cout << "Enter your ID: ";
//    while (!(cin >> ID))
//    {
//        cin.clear();
//        cin.ignore(INT_MAX, '\n');
//        cout << "Wrong input, please try again: ";
//    }cin.ignore(INT_MAX, '\n');
//
//    cout << "Enter your email: ";
//    getline(cin, email);
//
//    ofstream students;
//    students.open("students.txt", ios::app);
//    students << "\n" << ID << "\t" << firstName << "\t" << lastName << "\t" << email << "\t" << '0';
//
//    students.close();
//
//    enrolledCourseList* empty = NULL;  //because initially there are no enrolled courses
//
//    InsertAtQueue2(s, ID, firstName, lastName, email);
//    return ID;
//}

int signup(student* s)
{
    int ID;
    string firstName, lastName, email, password;
    cout << "Enter your first name: ";
    getline(cin, firstName);
    cout << "Enter your last name: ";
    getline(cin, lastName);
    srand(time(0)); //NULL
    ID = rand();

    DrawLines(70, '-');
    cout << "Your ID is: " << ID << "\n";
    email = to_string(ID) + "@ua.edu.lb";
    cout << "Your email is : " << email << endl;
    cout << "Now enter a password: " << endl;
    cout << "(must be at least 8 characters containing  numbers, letters and special characters)" << endl;
    do {
        cout << "Password: ";
        getline(cin, password);
    } while (verification_password(password) == false);


    DrawLines(70, '-');

    ofstream students;
    students.open("students.txt", ios::app);
    students << "\n" << ID << "\t" << firstName << "\t" << lastName << "\t" << email << "\t" << password << '0';

    students.close();

    enrolledCourseList* empty = NULL;  //because initially there are no enrolled courses

    InsertAtQueue2(s, ID, 0, firstName, lastName, email);
    cout << "Press enter to continue...";
    string enter;
    getline(cin, enter);
    return ID;
}



bool courseExist(universityCourseList CL, int courseID)
{
    for (course* cur = CL.head; cur != NULL; cur = cur->next)
        if (cur->courseID == courseID)
            return true;
    return false;
}


void viewenrolledstudents(student* SL, universityCourseList CL)
{
    int courseid;
    //cout << SL->firstName;
    char c = 'y';
    while (c == 'y')
    {
        do {
            cout << "Enter the course ID you want to search for: ";
            cin >> courseid;
        } while (courseExist(CL, courseid) == false);
        cout << endl;
        bool enrolled = false;
        cout << "Enrolled Students in " << courseid << " are: " << endl;
        for (student* curs = SL; curs != NULL; curs = curs->next)
        {
            for (enrolledCourse* curec = curs->enrolledCourse.head; curec != NULL; curec = curec->next)
            {
                if (curec->courseReference->courseID == courseid)
                {
                    cout << curs->firstName << " " << curs->lastName << " " << curs->studentID << endl;
                    enrolled = true;
                }
            }
        }
        if (enrolled == false)
            cout << "0 students are enrolled" << endl;
        cout << endl;
        cout << "Search for another course? (y/n) : ";
        cin >> c;
        cout << endl;
    }
}


int alphabetOrder(string s1, string s2)   // return -1 if s1 before s2       and 1 if  s2 before s1
{
    int i = 0;
    while (i != s1.length() && i != s2.length())
    {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;

        i++;
    }
    return 0;
}

int dayOfWeek(Time x)
{
    if (x.day == "Mon")
        return 1;
    if (x.day == "Tue")
        return 2;
    if (x.day == "Wed")
        return 3;
    if (x.day == "Thu")
        return 4;
    if (x.day == "Fri")
        return 5;
    if (x.day == "Sat")
        return 6;
    return 0;
}

int chronologicalOrder(Time A, Time B)  // returns -1 if A before B and 1 if A after B
{
    if (dayOfWeek(A) < dayOfWeek(B))
        return -1;
    else if (dayOfWeek(A) > dayOfWeek(B))
        return 1;
    else if (A.startHour < B.startHour)
        return -1;
    else if (A.startHour > B.startHour)
        return 1;
    else if (A.startMin < B.startMin)
        return -1;
    else if (A.startMin > B.startMin)
        return 1;
    return 0;
}

void swap2(course*& A, course*& B)
{
    course* C;
    C = A;
    A = B;
    B = C;
}

void viewCourses(student* sl, int id)
{
    char c = 'y';
    student* cur = sl;
    while (cur != NULL && cur->studentID != id)
    {
        cur = cur->next;
    }
    while (c == 'y')
    {
        enrolledCourseList studentCourse;
        studentCourse.head = NULL;
        studentCourse.tail = NULL;

        if (cur->courseNb == 0) {
            cout << "You have no courses enrolled yet." << endl;
            return;
        }

        for (student* curs = sl; curs != NULL; curs = curs->next)
        {
            if (curs->studentID == id && curs->enrolledCourse.head == NULL)
                return;
            if (curs->studentID == id)
            {
                studentCourse = curs->enrolledCourse;
            }
        }

        int choice;
        cout << "Do you want to see you schedule sorted by alphabetical or chronological order ?" << endl;
        do {
            cout << "Press 1 for alphabetical or 2 for chnological: ";
            cin >> choice;
        } while (choice < 1 || choice > 2);


        if (choice == 1)
        {

            for (enrolledCourse* curec1 = studentCourse.head; curec1 != NULL; curec1 = curec1->next)
            {
                for (enrolledCourse* curec2 = studentCourse.head; curec2 != NULL; curec2 = curec2->next)
                {
                    if (alphabetOrder(curec1->courseReference->courseName, curec2->courseReference->courseName) == -1)
                    {
                        if (curec1 == studentCourse.head)
                            swap2(studentCourse.head->courseReference, curec2->courseReference);
                        else
                            swap2(curec1->courseReference, curec2->courseReference);
                    }
                }
            }
        }

        else {


            for (enrolledCourse* curec1 = studentCourse.head; curec1 != NULL; curec1 = curec1->next)
            {
                for (enrolledCourse* curec2 = studentCourse.head; curec2 != NULL; curec2 = curec2->next)
                {
                    if (chronologicalOrder(curec1->courseReference->timeSchedule, curec2->courseReference->timeSchedule) == -1)
                    {
                        if (curec1 == studentCourse.head)
                            swap2(studentCourse.head->courseReference, curec2->courseReference);
                        else
                            swap2(curec1->courseReference, curec2->courseReference);
                    }
                }
            }

        }

        for (student* curs = sl; curs != NULL; curs = curs->next)
        {
            if (id == curs->studentID)
                for (enrolledCourse* curec = curs->enrolledCourse.head; curec != NULL; curec = curec->next)
                {
                    cout << curec->courseReference->courseID << " ";
                    cout << curec->courseReference->courseName << " ";
                    cout << curec->courseReference->instructorName << " ";
                    cout << curec->courseReference->timeSchedule.day << " ";
                    cout << curec->courseReference->timeSchedule.startHour << ":";

                    if (curec->courseReference->timeSchedule.startMin < 10)
                        cout << "0" << curec->courseReference->timeSchedule.startMin << " ";
                    else
                        cout << curec->courseReference->timeSchedule.startMin << " ";

                    cout << curec->courseReference->timeSchedule.endHour << ":";

                    if (curec->courseReference->timeSchedule.endMin < 10)
                        cout << "0" << curec->courseReference->timeSchedule.endMin << " ";
                    else
                        cout << curec->courseReference->timeSchedule.endMin;

                    if (curec->att == 1) {
                        cout << " Present - ";
                    }
                    else
                        cout << " Absent - ";
                    cout << "Grade: " << curec->grade << "/100";
                    cout << endl;
                }
        }

        do {
            cout << "Recheck you schedule (y/n) ? :";
            cin >> c;
        } while (c != 'y' && c != 'n');
    }
}

void insertAtQueueEC(student*& s, course*& c)
{
    enrolledCourse* tmp = new enrolledCourse;

    tmp->courseReference = c;
    tmp->next = NULL;
    tmp->previous = NULL;

    //cout << s->enrolledCourse.head->courseReference->courseID;

    if (s->enrolledCourse.head == NULL || s->enrolledCourse.tail == NULL) {
        s->enrolledCourse.head = tmp;
        s->enrolledCourse.tail = tmp;
    }

    tmp->previous = s->enrolledCourse.tail;
    s->enrolledCourse.tail->next = tmp;
    s->enrolledCourse.tail = tmp;
}

void fillCourseFile(universityCourseList* ucl)
{
    fstream a;
    a.open("courses.txt", ios::out);

    for (course* curC = ucl->head; curC != NULL; curC = curC->next)
    {
        a << curC->courseID << "\t";
        a << curC->courseCapacity << "\t";
        a << curC->attendeeNb << "\t";
        a << curC->courseName << "\t";
        a << curC->instructorName << "\t";
        a << curC->timeSchedule.day << "\t";
        a << curC->timeSchedule.startHour << ":";

        if (curC->timeSchedule.startMin < 10)
            a << "0" << curC->timeSchedule.startMin << "\t";
        else
            a << curC->timeSchedule.startMin << "\t";

        a << curC->timeSchedule.endHour << ":";

        if (curC->timeSchedule.endMin < 10)
            a << "0" << curC->timeSchedule.endMin << "\t";
        else
            a << curC->timeSchedule.endMin;
        a << endl;
    }

    a.close();
}

void fillInfo(student* s)
{
    fstream a;
    a.open("info.txt", ios::out);

    for (student* cur = s; cur != NULL; cur = cur->next)
    {
        a << cur->studentID << "\t";
        for (enrolledCourse* curEC = cur->enrolledCourse.head; curEC != NULL; curEC = curEC->next)
        {
            a << curEC->courseReference->courseID << "\t" << curEC->att << "\t" << curEC->grade << "\t";
        }
        a << endl;
    }

    a.close();
}

void addCourse(student*& sl, universityCourseList* ucl, int id)
{
    char c = 'y';
    while (c == 'y')
    {
        int choice;
        cout << "1) View all courses.\n";
        cout << "2) View open courses only.\n";
        cout << "3) See the list of other students that are already enrolled in a particular course.\n";
        cout << "4) Add courses.\n\n";
        cin >> choice;
        while (choice < 1 || choice>4) {
            cout << "Please enter a number between 1 and 4\n";
            cin >> choice;
        }

        if (choice == 1)
        {
            PrintListH2R(*ucl);
        }

        if (choice == 2) {
            cout << "The courses available for you are: " << endl;
            enrolledCourse* curEC;

            for (student* cur = sl; cur != NULL; cur = cur->next)
            {
                if (cur->studentID == id)
                {
                    for (course* curC = ucl->head; curC != NULL; curC = curC->next)
                    {
                        int a = 0;
                        if (curC->attendeeNb < curC->courseCapacity) {
                            for (curEC = cur->enrolledCourse.head; curEC != NULL; curEC = curEC->next)
                            {
                                {
                                    if (curC->courseID == curEC->courseReference->courseID || curC->courseName == curEC->courseReference->courseName)
                                    {
                                        a = 1;
                                        break;
                                    }
                                }
                            }

                            if (a != 1)
                            {
                                cout << curC->courseID << " ";
                                cout << curC->courseName << " ";
                                cout << curC->instructorName << " ";
                                cout << curC->timeSchedule.day << " ";
                                cout << curC->timeSchedule.startHour << ":";

                                if (curC->timeSchedule.startMin < 10)
                                    cout << "0" << curC->timeSchedule.startMin << " ";
                                else
                                    cout << curC->timeSchedule.startMin << " ";

                                cout << curC->timeSchedule.endHour << ":";

                                if (curC->timeSchedule.endMin < 10)
                                    cout << "0" << curC->timeSchedule.endMin << " ";
                                else
                                    cout << curC->timeSchedule.endMin;
                                cout << endl;
                            }
                        }
                    }
                }
            }
        }


        if (choice == 3) {
            viewenrolledstudents(sl, *ucl);
        }


        if (choice == 4) {
            int a;
            int courseID;

            do {
                a = 1;
                cout << "Enter the ID of the course you want to add: ";
                cin >> courseID;
                for (course* curC = ucl->head; curC != NULL; curC = curC->next)
                {
                    if (curC->courseID == courseID)
                    {
                        cout << curC->courseName;
                        if (curC->attendeeNb == curC->courseCapacity)
                        {
                            a = 0;
                            cout << "This course if full. \n";
                            break;
                        }
                        for (student* curS = sl; curS != NULL; curS = curS->next)
                        {
                            if (curS->studentID == id)
                            {
                                for (enrolledCourse* curEC = curS->enrolledCourse.head; curEC != NULL; curEC = curEC->next)
                                {
                                    if (curEC->courseReference->courseID == courseID || curEC->courseReference->courseName == curC->courseName)
                                    {
                                        a = 0;
                                        cout << "You have already registered this course. \n";
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }

            } while (a == 0);

            course* c = ucl->head;
            for (c; c->courseID != courseID; c = c->next);


            student* s = sl;
            for (s; s->studentID != id; s = s->next);

            cout << "You can enroll this course" << endl;
            c->attendeeNb++;
            s->courseNb++;

            insertAtQueueEC(s, c);
        }

        cout << "Continue? (y/n) : ";
        cin >> c;
    }

    fstream a;
    a.open("students.txt", ios::out);

    for (student* curS = sl; curS != NULL; curS = curS->next)
    {
        a << curS->studentID << "\t" << curS->firstName << "\t" << curS->lastName << "\t" << curS->emailAddress << "\t" << curS->password << "\t" << curS->courseNb << "\t";
        for (enrolledCourse* ecd = curS->enrolledCourse.head; ecd != NULL; ecd = ecd->next)
        {
            a << ecd->courseReference->courseID << "\t";
        }

        a << "\n";
    }
    a.close();

    fillCourseFile(ucl);
    fillInfo(sl);
}

void deleteCourse(student*& sl, universityCourseList*& ucl, int id)
{
    char c = 'y';

    /*for (student* curS = sl; curS != NULL; curS = curS->next)
    {
        cout << curS->studentID << "\t" << curS->firstName << "\t" << curS->lastName << "\t" << curS->emailAddress << "\t" << curS->courseNb << "\t";
        for (enrolledCourse* ecd = curS->enrolledCourse.head; ecd != NULL; ecd = ecd->next)
        {
            cout << ecd->courseReference->courseID << "\t";
        }

        cout << "\n";
    }*/

    while (c == 'y')
    {
        int choice;
        cout << "1) View your schedule.\n";
        cout << "2) See the list of other students that are already enrolled in a particular course.\n";
        cout << "3) Delete courses.\n\n";
        cin >> choice;
        while (choice < 1 || choice>3)
        {
            cout << "Please enter a number between 1 and 3\n";
            cin >> choice;
        }

        if (choice == 1)
        {
            viewCourses(sl, id);
        }



        if (choice == 2)
        {
            viewenrolledstudents(sl, *ucl);
        }


        if (choice == 3)
        {
            int a;
            int courseID;

            do {
                a = 1;
                cout << "Enter the ID of the course you want to delete: ";
                cin >> courseID;
                while (!courseExist(*ucl, courseID))
                {
                    a = 0;
                    cout << "The course doesn't exit. \n";
                    break;
                }
                for (course* curC = ucl->head; curC != NULL; curC = curC->next)
                {
                    if (curC->courseID == courseID)
                    {
                        for (student* curS = sl; curS != NULL; curS = curS->next)
                        {
                            if (curS->studentID == id)
                            {
                                if (curS->enrolledCourse.head->courseReference->courseID == courseID)
                                {
                                    // Update the head pointer to point to the next element in the list before deleting the current head element
                                    enrolledCourse* temp = curS->enrolledCourse.head;
                                    curS->enrolledCourse.head = curS->enrolledCourse.head->next;
                                    delete temp;
                                    curS->courseNb--;
                                    curC->attendeeNb--;
                                    // Make sure to update the next element's previous pointer if it exists
                                    if (curS->enrolledCourse.head != NULL)
                                    {
                                        curS->enrolledCourse.head->previous = NULL;
                                    }
                                }
                                else if (curS->enrolledCourse.tail->courseReference->courseID == courseID)
                                {
                                    // Update the tail pointer to point to the previous element in the list before deleting the current tail element
                                    enrolledCourse* temp = curS->enrolledCourse.tail;
                                    curS->enrolledCourse.tail = curS->enrolledCourse.tail->previous;
                                    delete temp;
                                    curS->courseNb--;
                                    curC->attendeeNb--;
                                    // Make sure to update the previous element's next pointer if it exists
                                    if (curS->enrolledCourse.tail != NULL)
                                    {
                                        curS->enrolledCourse.tail->next = NULL;
                                    }
                                }
                                else {
                                    for (enrolledCourse* curEC = curS->enrolledCourse.head; curEC != NULL; curEC = curEC->next)
                                    {
                                        if (curEC->courseReference->courseID == courseID)
                                        {
                                            curEC->previous->next = curEC->next;
                                            curEC->next->previous = curEC->previous;
                                            delete curEC;
                                            curS->courseNb--;
                                            curC->attendeeNb--;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }

            } while (a == 0);
        }
        cout << "Continue? (y/n) : ";
        cin >> c;
    }
    /*for (student* curS = sl; curS != NULL; curS = curS->next)
    {
        cout << curS->studentID << "\t" << curS->firstName << "\t" << curS->lastName << "\t" << curS->emailAddress << "\t" << curS->courseNb << "\t";
        for (enrolledCourse* ecd = curS->enrolledCourse.head; ecd != NULL; ecd = ecd->next)
        {
            cout << ecd->courseReference->courseID << "\t";
        }

        cout << "\n";
    }*/

    fstream a;
    a.open("students.txt", ios::out);

    for (student* curS = sl; curS != NULL; curS = curS->next)
    {
        a << curS->studentID << "\t" << curS->firstName << "\t" << curS->lastName << "\t" << curS->emailAddress << "\t" << curS->password << "\t" << curS->courseNb << "\t";
        for (enrolledCourse* ecd = curS->enrolledCourse.head; ecd != NULL; ecd = ecd->next)
        {
            a << ecd->courseReference->courseID << "\t";
        }
        a << "\n";
    }
    a.close();

    fillCourseFile(ucl);
    fillInfo(sl);
}

void swapCourses(student*& sl, universityCourseList*& ucl, int studentID)
{
    // Find the student in the linked list
    student* curS = NULL;
    for (student* s = sl; s != NULL; s = s->next)
    {
        if (s->studentID == studentID) {
            curS = s;
            break;
        }
    }
    if (curS == NULL) {
        cout << "Student not found." << endl;
        return;
    }

    // Print the student's enrolled courses
    cout << "Your enrolled courses: " << endl;
    for (enrolledCourse* ec = curS->enrolledCourse.head; ec != NULL; ec = ec->next)
    {
        cout << ec->courseReference->courseID << " - " << ec->courseReference->courseName << endl;
    }

    // Print the available courses
    cout << "The courses available for you are: " << endl;
    enrolledCourse* curEC;

    for (student* cur = sl; cur != NULL; cur = cur->next)
    {
        if (cur->studentID == studentID)
        {
            for (course* curC = ucl->head; curC != NULL; curC = curC->next)
            {
                int a = 0;
                if (curC->attendeeNb < curC->courseCapacity) {
                    for (curEC = cur->enrolledCourse.head; curEC != NULL; curEC = curEC->next)
                    {
                        {
                            if (curC->courseID == curEC->courseReference->courseID)
                            {
                                a = 1;
                                break;
                            }
                        }
                    }

                    if (a != 1)
                    {
                        cout << curC->courseID << " ";
                        cout << curC->courseName << " ";
                        cout << curC->instructorName << " ";
                        cout << curC->timeSchedule.day << " ";
                        cout << curC->timeSchedule.startHour << ":";

                        if (curC->timeSchedule.startMin < 10)
                            cout << "0" << curC->timeSchedule.startMin << " ";
                        else
                            cout << curC->timeSchedule.startMin << " ";

                        cout << curC->timeSchedule.endHour << ":";

                        if (curC->timeSchedule.endMin < 10)
                            cout << "0" << curC->timeSchedule.endMin << " ";
                        else
                            cout << curC->timeSchedule.endMin;
                        cout << endl;
                    }
                }
            }
        }
    }

    // Get the IDs of the courses to swap
    int oldCourseID, newCourseID;
    cout << "Enter the ID of the course to replace: ";
    cin >> oldCourseID;
    cout << "Enter the ID of the new course: ";
    cin >> newCourseID;

    // Find the old course in the student's enrolled courses list
    enrolledCourse* oldEC = NULL;
    for (enrolledCourse* ec = curS->enrolledCourse.head; ec != NULL; ec = ec->next)
    {
        if (ec->courseReference->courseID == oldCourseID)
        {
            oldEC = ec;
            break;
        }
    }
    if (oldEC == NULL)
    {
        cout << "The student is not enrolled in the old course." << endl;
        return;
    }

    // Find the new course in the university courses list
    course* newC = NULL;
    for (course* c = ucl->head; c != NULL; c = c->next)
    {
        if (c->courseID == newCourseID)
        {
            newC = c;
            break;
        }
    }
    if (newC == NULL)
    {
        cout << "The new course was not found in the university courses list." << endl;
        return;
    }

    // Update the attendee count for the old and new courses
    for (course* curC = ucl->head; curC != NULL; curC = curC->next) {
        if (curC->courseID == oldCourseID) {
            curC->attendeeNb--;
            break;
        }
    }
    for (course* curC = ucl->head; curC != NULL; curC = curC->next)
    {
        if (curC->courseID == newCourseID)
        {
            curC->attendeeNb++;
            break;
        }
    }

    // Swap the courses in the student's enrolled courses list
    oldEC->courseReference = newC;
    cout << "Course successfully swapped." << endl;

    fstream a;
    a.open("students.txt", ios::out);

    for (student* curS = sl; curS != NULL; curS = curS->next)
    {
        a << curS->studentID << "\t" << curS->firstName << "\t" << curS->lastName << "\t" << curS->emailAddress << "\t" << curS->password << "\t" << curS->courseNb << "\t";
        for (enrolledCourse* ecd = curS->enrolledCourse.head; ecd != NULL; ecd = ecd->next)
        {
            a << ecd->courseReference->courseID << "\t";
        }

        a << "\n";
    }
    a.close();

    fillCourseFile(ucl);
    fillInfo(sl);
}

void viewInstructorCourses(universityCourseList* ucl, instructorList* il, string id)
{
    course* cur = ucl->head;
    while (cur != NULL) {
        if (cur->instructorName == id) {
            cout << cur->courseName << "-" << cur->courseID << endl;
        }
        cur = cur->next;
    }
    cout << endl;
}

void readAtt(student*& sl)
{
    fstream attendanceFile("info.txt", ios::in | ios::out | ios::app);
    student* cur = sl;
    int courseID, studentID;
    while (attendanceFile)
    {
        attendanceFile >> studentID;
        for (cur = sl;cur != NULL;cur = cur->next)
        {
            if (cur->studentID == studentID)
            {
                enrolledCourse* curec;
                curec = cur->enrolledCourse.head;
                while (curec != NULL) {
                    attendanceFile >> courseID;
                    enrolledCourse* curec2 = cur->enrolledCourse.head;
                    while (curec2 != NULL) {
                        if (curec2->courseReference->courseID == courseID) {
                            attendanceFile >> curec2->att;
                            attendanceFile >> curec2->grade;
                        }
                        curec2 = curec2->next;
                    }
                    curec = curec->next;
                }
            }
        }
    }
    attendanceFile.close();
}


void att(universityCourseList* cl, student*& sl, string instructName) {
    int courseID;
    cout << "Enter the course ID: ";
    cin >> courseID;
    student* cur;
    cur = sl;
    while (cur != NULL) {
        enrolledCourse* curec = cur->enrolledCourse.head;
        while (curec != NULL) {
            if (curec->courseReference->courseID == courseID) {
                cout << cur->studentID << " " << cur->firstName << " " << cur->lastName << " : ";
                cin >> curec->att;
            }
            curec = curec->next;
        }
        cur = cur->next;
    }

}

void grade(universityCourseList* cl, student*& sl, string instructName) {
    int courseID;
    cout << "Enter the course ID: ";
    cin >> courseID;
    student* cur;
    cur = sl;
    /*
    for(course *curC = cl->head; curC!=NULL; curC = curC->next)
    {
        if(curC->courseID == courseID)
        {
            if(curC->attendeeNb == 0)
            {
                cout<<"There are no students enrolled in this course. \n";
            }
        }
    }*/
    while (cur != NULL) {
        enrolledCourse* curec = cur->enrolledCourse.head;
        while (curec != NULL) {
            if (curec->courseReference->courseID == courseID) {
                cout << cur->studentID << " " << cur->firstName << " " << cur->lastName << " : ";
                cin >> curec->grade;
            }
            curec = curec->next;
        }


        cur = cur->next;
    }

}


void writeOnFile(student* sl) {
    fstream attf("info.txt", ios::out);
    for (student* curs = sl;curs != NULL;curs = curs->next) {
        attf << curs->studentID;
        for (enrolledCourse* curec = curs->enrolledCourse.head;curec != NULL;curec = curec->next) {
            attf << "\t" << curec->courseReference->courseID;
            attf << "\t" << curec->att << "\t" << curec->grade;
        }
        attf << "\n";
    }
    attf.close();
}




int main()
{
    student* s = new student;
    s = NULL;



    universityCourseList* courseList = new universityCourseList;
    courseList->head = NULL;
    courseList->tail = NULL;

    fillCourses(courseList);
    fillStudents(s, courseList);
    fillAttendees(s, courseList);
    readAtt(s);

    instructorList* e = new instructorList;
    e->head = NULL;
    e->tail = NULL;
    fillInstructor(e);

    int choice;
    DrawLines(75, '_');
    cout << "\n\n\n\t\t\tStudent Information System\n\n\n";
    DrawLines(75, '_');
    cout << endl;
    do {
        cout << "(1) Sign In | (2) Sign Up" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2);
    cin.ignore(INT_MAX, '\n');
    system("cls");
    int loggedInStudent;
    if (choice == 1) {
        int n;
        cout << "1-Login as student\n2-Login as instructor\n";
        do
        {
            cin >> n;
        } while (n < 1 || n>2);
        cin.ignore(INT_MAX, '\n');

        if (n == 1)
        {
            loggedInStudent = login(s);
            system("cls");
            int option;

            do {

                cout << "What are you going to do ?\n\n";
                cout << "1) Check your course schedule.\n";
                cout << "2) Add new courses.\n";
                cout << "3) Drop already enrolled courses.\n";
                cout << "4) Swap two courses.\n";
                cout << "5) Quit. \n";
                cout << "Choose an option: ";
                cin >> option;
                while (option < 1 || option>5) {
                    cout << "Please enter only a number between 1 and 5: ";
                    cin >> option;
                }
                if (option == 1)
                    viewCourses(s, loggedInStudent);
                else if (option == 2)
                    addCourse(s, courseList, loggedInStudent);
                else if (option == 3)
                    deleteCourse(s, courseList, loggedInStudent);
                else if (option == 4)
                    swapCourses(s, courseList, loggedInStudent);
            } while (option != 5);
        }
        else {
            string loggedin = loginInstructor(e);
            int k;

            system("cls");

            do {

                cout << "1) Check the list of courses that you teache.\n";
                cout << "2) Class attendance.\n";
                cout << "3) Add grades. \n";
                cout << "4) Quit. \n";
                cin >> k;
                while (k < 1 || k>4)
                {
                    cout << "Please choose a number between 1 and 4: ";
                    cin >> k;
                }
                if (k == 1) {
                    viewInstructorCourses(courseList, e, loggedin);
                }
                else if (k == 2) {

                    att(courseList, s, loggedin);
                    writeOnFile(s);
                }
                else if (k == 3) {

                    grade(courseList, s, loggedin);
                    writeOnFile(s);
                }
            } while (k != 4);
        }


    }

    else {
        loggedInStudent = signup(s);
        system("cls");
        int option;
        do {

            cout << "What are you going to do ?\n\n";
            cout << "1) Check your course schedule.\n";
            cout << "2) Add new courses.\n";
            cout << "3) Drop already enrolled courses.\n";
            cout << "4) Swap two courses.\n\n";
            cout << "5) Quit. \n";
            cout << "Choose an option: ";
            cin >> option;
            while (option < 1 || option>5) {
                cout << "Please enter only a number between 1 and 5: ";
                cin >> option;
            }
            if (option == 1)
                viewCourses(s, loggedInStudent);
            else if (option == 2)
                addCourse(s, courseList, loggedInStudent);
            else if (option == 3)
                deleteCourse(s, courseList, loggedInStudent);
            else if (option == 4)
                swapCourses(s, courseList, loggedInStudent);
        } while (option != 5);
    }
    //system("cls");

    //PrintList(s);
    //PrintListH2R(*courseList);
}
