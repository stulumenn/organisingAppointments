#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

enum gender {MALE =0, FEMALE};
typedef enum gender Gender_t;
enum months {JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
typedef enum months Months_t;

typedef struct
{
	int hour;
	int minute;
}Time_t;

typedef struct 
{
	int firstHalf;
	int secondHalf;
}TCId_no_t;

typedef struct
{
	TCId_no_t idNo;
	char name[30];
	char surname[30];
	Gender_t gender;
}People_t;

typedef struct
{
	int year;
	Months_t month;
	int day;
	Time_t time;
}Date_t;

typedef struct
{
	People_t people;
	Date_t date;
}Appointment_t;

int getPeople (const char *fileName, People_t people[], int maxSize);
int getAppointments (const char *fileName, Appointment_t appointments[], int maxSize);
void writeNames (Appointment_t appointments[], int sizeApp, const People_t people[], int sizePeople);
int checkAppointments (Appointment_t appointments[], int size);
void sortAppointments(Appointment_t appointments[], int size);
void writeAppointments(const char *fileName, Appointment_t appointments[], int size);

int main(){
	int newPeopleSize, newAppSize;
	People_t peopleArray[4];
	Appointment_t appointmentArray[10];
	int getMaxSize = 4;
	newPeopleSize = getPeople("People.txt", peopleArray, getMaxSize);
	newAppSize = getAppointments ("AppointmentReqs.txt", appointmentArray, getMaxSize);
	writeNames(appointmentArray,newAppSize, peopleArray, newPeopleSize);
	newAppSize = checkAppointments(appointmentArray, newAppSize);
	sortAppointments(appointmentArray, newAppSize);
	writeAppointments("Appointments.txt", appointmentArray, newAppSize);
	return 0;
}

int getPeople (const char *fileName, People_t people[], int maxSize){

	char character;
	FILE *fp = fopen (fileName, "r");
	int j;
	for(j=0; j<maxSize; j++)
	{
		fscanf (fp, "%6d%5d %s %s %c", &(people[j].idNo.firstHalf),
									    &(people[j].idNo.secondHalf),
									    people[j].name, 
									    people[j].surname, 
									    &character);
		switch (character){
			case 'M':
				people[j].gender = 0;
				break;
			case 'F':
				people[j].gender = 1;
				break;
			default:
				printf("This is not a gender.\n");
				break;
		}
	}
	return j;
}

int getAppointments (const char *fileName, Appointment_t appointments[], int maxSize){
	FILE *fp = fopen(fileName, "r");
	int i;
	for (i=0; i<maxSize; i++){
		fscanf(fp, "%6d%5d %d %d %d %d:%d", &(appointments[i].people.idNo.firstHalf), 
											&(appointments[i].people.idNo.secondHalf), 
											&(appointments[i].date.year), 
											&(appointments[i].date.month), 
											&(appointments[i].date.day), 
											&(appointments[i].date.time.hour), 
											&(appointments[i].date.time.minute));
	}
	return i;
}
void writeNames (Appointment_t appointments[], int sizeApp, const People_t people[], int sizePeople){
	for(int i=0; i<sizePeople; i++){
		for(int j=0; j<sizeApp; j++){
			if ((appointments[i].people.idNo.firstHalf == people[j].idNo.firstHalf) 
				&& (appointments[i].people.idNo.secondHalf == people[j].idNo.secondHalf)){
				strcpy (appointments[i].people.name, people[j].name);
				strcpy (appointments[i].people.surname, people[j].surname);
				appointments[i].people.gender = people[j].gender;
			}
		}
	}
}
int checkAppointments (Appointment_t appointments[], int size){

	int newSize = size;

	for (int i=0; i<size-1; i++){
		for (int j=i+1; j<size; j++){
			if ((appointments[i].date.year == appointments[j].date.year)
				&&(appointments[i].date.month == appointments[j].date.month)
				&&(appointments[i].date.day == appointments[j].date.day)
				&&(appointments[i].date.time.hour == appointments[j].date.time.hour)
				&&(appointments[i].date.time.minute == appointments[j].date.time.minute)){
				
				for(int z = j+1; z<size; z++){
					appointments[z].people.idNo.firstHalf = appointments[z+1].people.idNo.firstHalf;
					appointments[z].people.idNo.secondHalf= appointments[z+1].people.idNo.secondHalf;
					strcpy(appointments[z].people.name, appointments[z+1].people.name);
					strcpy(appointments[z].people.surname, appointments[z+1].people.surname);
					appointments[z].people.gender = appointments[z+1].people.gender;
				}
				--newSize;
			}
		}
	}
	return newSize;
}
void sortAppointments(Appointment_t appointments[], int size){
	for(int i=0; i<size-1; i++){
		for(int j=i+1; j<size; j++){
			if((appointments[i].date.year > appointments[j].date.year) 
				|| (appointments[i].date.month > appointments[j].date.month) 
				|| (appointments[i].date.day > appointments[j].date.day) 
				|| (appointments[i].date.time.hour > appointments[j].date.time.hour) 
				|| (appointments[i].date.time.minute > appointments[j].date.time.minute)){
				
				int tempIdNoFirstHalf,tempIdNoSecondHalf, tempGender, tempYear, tempMonth, tempDay, tempHour, tempMinute;
				char tempName[30];
				char tempSurname[30];

				tempIdNoFirstHalf = appointments[i].people.idNo.firstHalf;
				tempIdNoSecondHalf = appointments[i].people.idNo.secondHalf;
				tempGender = appointments[i].people.gender;
				tempYear = appointments[i].date.year;
				tempMonth = appointments[i].date.month;
				tempDay = appointments[i].date.day;
				tempHour = appointments[i].date.time.hour;
				tempMinute = appointments[i].date.time.minute;
				strcpy(tempName, appointments[i].people.name);
				strcpy(tempSurname, appointments[i].people.surname);

				appointments[i].people.idNo.firstHalf = appointments[j].people.idNo.firstHalf;
				appointments[i].people.idNo.secondHalf = appointments[j].people.idNo.secondHalf;
				appointments[i].people.gender = appointments[j].people.gender;
				appointments[i].date.year = appointments[j].date.year;
				appointments[i].date.month = appointments[j].date.month;
				appointments[i].date.day = appointments[j].date.day;
				appointments[i].date.time.hour = appointments[j].date.time.hour;
				appointments[i].date.time.minute = appointments[j].date.time.minute;
				strcpy(appointments[i].people.name, appointments[j].people.name);
				strcpy(appointments[i].people.surname, appointments[j].people.surname);

				appointments[j].people.idNo.firstHalf = tempIdNoFirstHalf;
				appointments[j].people.idNo.secondHalf= tempIdNoSecondHalf;
				appointments[j].people.gender = tempGender;
				appointments[j].date.year = tempYear;
				appointments[j].date.month = tempMonth;
				appointments[j].date.day = tempDay;
				appointments[j].date.time.hour = tempHour;
				appointments[j].date.time.minute = tempMinute;
				strcpy(appointments[j].people.name, tempName);
				strcpy(appointments[j].people.surname, tempSurname);
			}
		}
	}
}
void writeAppointments(const char *fileName, Appointment_t appointments[], int size){
	FILE *fp = fopen (fileName, "w");
	for(int i=0; i<size; i++){
		fprintf(fp, "%d %d %d %d:%d %d%d %s %s %d\n", appointments[i].date.year,
													 appointments[i].date.month, 
													 appointments[i].date.day, 
													 appointments[i].date.time.hour, 
													 appointments[i].date.time.minute, 
													 appointments[i].people.idNo.firstHalf, 
													 appointments[i].people.idNo.secondHalf, 
													 appointments[i].people.name, 
													 appointments[i].people.surname, 
													 appointments[i].people.gender);
	}
	fclose(fp);
}






