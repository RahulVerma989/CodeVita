#include<bits/stdc++.h>
using namespace std;

//student datatype
struct Student{
    int id;
    float percentage;
    int choice[3];
    bool admitted = false;
    int collegeId = -1;
};


vector<string> splitString(string s, string seperator=",")
{
    vector<string> array;
    string str;
    int start = 0;
    int end = s.find(seperator);
    while(end != s.npos)
    {
        str = s.substr(start,end - start);
        array.push_back(str);
        start = end+seperator.length();
        end = s.find(seperator,start);
    }
    if(end == s.npos)
    {
        str = s.substr(start,s.length() - start);
        array.push_back(str);
    }

    return array;
}

int stringToInt(string s)
{
    int num = 0;
    stringstream ss(s);
  	ss >> num;
    return num;
}

float stringToFloat(string s)
{
    float number = 0.0;
    stringstream ss(s);
    ss >> number;
    return number;
}

float getTwoDecimalFloat(float number)
{
    //let the number is 14.66666...
    //then 14.6666*100 = 1466.6666
    //type cast to int => 1466
    //type cast to float
    float value = (int)(number*100);
    return (float)value/100; 
}

bool compareTwoStudents(Student *a, Student *b)
{
    //if percentage is not equal then return true for higher percentage
    if(a->percentage != b->percentage)
        return (a->percentage > b->percentage);
    
    //percentage is equal of both the students are equal then compare with 
    //their id
    return (a->id > b->id);
}

int main()
{
    int c,n;

    //Number of colleges and Number of students
    cin>>c>>n;

    int seats[c];

    //seats per college
    for(int i = 0; i < c; i++)
    {
        cin>>seats[i];
    }

    //creating an array of type students
    vector<Student> students(n);
    //pointers pointing to students
    vector<Student *> studentPointer(n);
    string temp = "";
    vector<string> studentData;

    //getting students data
    int i = 0;
    for(int i = 0; i < n; i++)
    {
        //gets student data
        cin>>temp;
        studentData.push_back(temp);
    }

    //inserting students data
    for(int i = 0; i < n; i++)
    {
         //splitting commas
        vector<string> tempArr;
        tempArr = splitString(studentData[i]);
        students[i].id = stringToInt(splitString(tempArr[0],"-")[1]);
        students[i].percentage = getTwoDecimalFloat(stringToFloat(tempArr[1]));

        //inserting choices
        for(int c = 0; c < 3; c++)
        {
            students[i].choice[c] = stringToInt(splitString(tempArr[2 + c],"-")[1]);
        }

        //stores pointers to each student
        studentPointer[i] = &students[i];
    }

    //sorting the student pointer array according to their percentage 
    //if their percentage is same then sorted according to their id
    sort(studentPointer.begin(),studentPointer.end(),compareTwoStudents);

    //now fill the seats in colleges
    //loop for choices
    for(int c = 0; c < 3; c++)
    {
        //loop for students
        for(int s = 0; s < n; s++)
        {
            //check if the student has already alotted a seat or not 
            if(!(studentPointer[s]->admitted))
            {
                //getting student's college preference and calculating the college index
                // that is college 1 has college index 0.
                int college = studentPointer[s]->choice[c] - 1;
                //if a seat is available in that college than admit that student in that college
                //that is reduce one seat in that college.
                if(seats[college])
                {
                    seats[college]--;
                    //now we don't want to reserve another seat for that student in another college
                    //therefore update the admission state for that student.
                    studentPointer[s]->admitted = true; 
                    studentPointer[s]->collegeId = college + 1;
                }
            }
            else
            {
                //skip this student, check for next student
                continue;
            }
        }
    }

    //printing the student id and college id of the students who got admitted
    for(int s = 0; s < n; s++)
    {
        Student student;
        student = (*studentPointer[s]);
        if(student.admitted)
            cout<<"Student-"<<student.id<<" C-"<<student.collegeId<<endl;
    }

    return 0;
}