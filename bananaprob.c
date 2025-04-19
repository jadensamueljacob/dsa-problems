#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { head, data } TYPEFIELD;

typedef struct appointmentNode 
{
    char time[6];
    struct appointmentNode *next;
} APPOINTMENTNODE;

typedef struct doctorNode 
{
    int doctorID;
    struct doctorNode *next;
    APPOINTMENTNODE *appointments; 
} DOCTORNODE;

typedef struct patientNode 
{
    int patientID;
    struct patientNode *next;
    APPOINTMENTNODE *appointments; 
} PATIENTNODE;

typedef struct multiList 
{
    DOCTORNODE *doctorList;
    PATIENTNODE *patientList;
} MULTILIST;

MULTILIST* init(TYPEFIELD tag) 
{
    MULTILIST *ml = (MULTILIST*)malloc(sizeof(MULTILIST));
    ml->doctorList = NULL;
    ml->patientList = NULL;
    return ml;
}

int addDoctor(MULTILIST *p) 
{
    static int nextDoctorID = 1;
    DOCTORNODE *newDoctor = (DOCTORNODE*)malloc(sizeof(DOCTORNODE));
    newDoctor->doctorID = nextDoctorID++;
    newDoctor->appointments = NULL;
    newDoctor->next = p->doctorList;
    p->doctorList = newDoctor;
    return newDoctor->doctorID;
}

int addPatient(MULTILIST *p) 
{
    static int nextPatientID = 1;
    PATIENTNODE *newPatient = (PATIENTNODE*)malloc(sizeof(PATIENTNODE));
    newPatient->patientID = nextPatientID++;
    newPatient->appointments = NULL;
    newPatient->next = p->patientList;
    p->patientList = newPatient;
    return newPatient->patientID;
}

int addAppointment(MULTILIST *p, int docID, int patID, char *time) 
{
    DOCTORNODE *doctor = p->doctorList;
    while (doctor && doctor->doctorID != docID) 
    {
        doctor = doctor->next;
    }
    PATIENTNODE *patient = p->patientList;
    while (patient && patient->patientID != patID) 
    {
        patient = patient->next;
    }

    if (!doctor || !patient) 
    {
        printf("Doctor or Patient not found.\n");
        return -1;
    }
    APPOINTMENTNODE *newApp = (APPOINTMENTNODE*)malloc(sizeof(APPOINTMENTNODE));
    strcpy(newApp->time, time);
    newApp->next = doctor->appointments;
    doctor->appointments = newApp;
    newApp = (APPOINTMENTNODE*)malloc(sizeof(APPOINTMENTNODE));
    strcpy(newApp->time, time);
    newApp->next = patient->appointments;
    patient->appointments = newApp;

    return 0;
}

void deleteAppointment(MULTILIST *p, int docID, int patID, char *time) 
{
    DOCTORNODE *doctor = p->doctorList;
    while (doctor && doctor->doctorID != docID) 
    {
        doctor = doctor->next;
    }
    PATIENTNODE *patient = p->patientList;
    while (patient && patient->patientID != patID) 
    {
        patient = patient->next;
    }

    if (!doctor || !patient) 
    {
        printf("Doctor or Patient not found.\n");
        return;
    }

    APPOINTMENTNODE *prevDocApp = NULL, *currDocApp = doctor->appointments;
    while (currDocApp) 
    {
        if (strcmp(currDocApp->time, time) == 0) 
        {
            if (prevDocApp) 
            {
                prevDocApp->next = currDocApp->next;
            } 
            else 
            {
                doctor->appointments = currDocApp->next;
            }
            free(currDocApp);
            break;
        }
        prevDocApp = currDocApp;
        currDocApp = currDocApp->next;
    }
    APPOINTMENTNODE *prevPatApp = NULL, *currPatApp = patient->appointments;
    while (currPatApp)
    {
        if (strcmp(currPatApp->time, time) == 0) 
        {
            if (prevPatApp) 
            {
                prevPatApp->next = currPatApp->next;
            } 
            else 
            {
                patient->appointments = currPatApp->next;
            }
            free(currPatApp);
            break;
        }
        prevPatApp = currPatApp;
        currPatApp = currPatApp->next;
    }
    printf("Appointment at %s deleted for Doctor %d and Patient %d.\n", time, docID, patID);
}
void listAppDoc(MULTILIST *p, int docID) 
{
    DOCTORNODE *doctor = p->doctorList;
    while (doctor && doctor->doctorID != docID) 
    {
        doctor = doctor->next;
    }
    if (!doctor) 
    {
        printf("Doctor not found.\n");
        return;
    }

    APPOINTMENTNODE *current = doctor->appointments;
    while (current) 
    {
        printf("Appointment Time: %s\n", current->time);
        current = current->next;
    }
}

void listAppPat(MULTILIST *p, int patID) 
{
    PATIENTNODE *patient = p->patientList;
    while (patient && patient->patientID != patID) 
    {
        patient = patient->next;
    }

    if (!patient) 
    {
        printf("Patient not found.\n");
        return;
    }

    APPOINTMENTNODE *current = patient->appointments;
    while (current) 
    {
        printf("Appointment Time: %s\n", current->time);
        current = current->next;
    }
}
int main() 
{
    int ch, docID, patID, cont;
    char time[6];
    MULTILIST *p;
    p = init(data);

    printf("********************************************\n");
    printf("    HOSPITAL MANAGEMENT SYSTEM              \n");
    printf("********************************************\n");

    do 
    {
        printf("\nEnter your choice:");
        printf("\n1. Add doctor");
        printf("\n2. Add patient");
        printf("\n3. Add Appointment");
        printf("\n4. Delete Appointment");
        printf("\n5. List Appointments for a Doctor");
        printf("\n6. List Appointments for a Patient");
        printf("\n7. Exit");
        printf("\nChoice: ");
        scanf("%d", &ch);

        switch (ch) 
        {
            case 1:
                docID = addDoctor(p);
                printf("\nDoctor inserted with doctor ID: %d", docID);
                break;
            case 2:
                patID = addPatient(p);
                printf("\nPatient inserted with patient ID: %d", patID);
                break;
            case 3:
                printf("\nEnter the doctor ID: ");
                scanf("%d", &docID);
                printf("\nEnter the patient ID: ");
                scanf("%d", &patID);
                printf("\nEnter the appointment time (HH:MM): ");
                scanf("%s", time);
                addAppointment(p, docID, patID, time);
                break;
            case 4:
                printf("\nEnter the doctor ID: ");
                scanf("%d", &docID);
                printf("\nEnter the patient ID: ");
                scanf("%d", &patID);
                printf("\nEnter the appointment time (HH:MM): ");
                scanf("%s", time);
                deleteAppointment(p, docID, patID, time);
                break;

            case 5:
                printf("\nEnter the doctor ID: ");
                scanf("%d", &docID);
                listAppDoc(p, docID);
                break;
            case 6:
                printf("\nEnter the patient ID: ");
                scanf("%d", &patID);
                listAppPat(p, patID);
                break;
            case 7:
                exit(0);
            default:
                printf("\nInvalid choice");
        }
        printf("\nDo you want to continue? Press 1 for Yes, 0 for No: ");
        scanf("%d", &cont);
    } while (cont);
    
    return 0;
}
