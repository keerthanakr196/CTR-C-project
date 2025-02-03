#include <stdio.h>
#include <string.h>
#define MAX_CANDIDATES 50
#define MAX_VOTERS 100
struct Candidate {
    char name[50];
    int votes;
};
struct Voter {
    char name[50];
    char voterID[10];
    char password[20];
    int hasVoted;
};

struct Candidate candidates[MAX_CANDIDATES];
struct Voter voters[MAX_VOTERS];
int candidateCount = 0, voterCount = 0;
void addCandidates() {
    printf("Enter the number of candidates: ");
    scanf("%d", &candidateCount);
    for (int i = 0; i < candidateCount; i++) {
        printf("Candidate %d: ", i + 1);
        scanf(" %[^\n]", candidates[i].name);
        candidates[i].votes = 0;
    }
}
void viewCandidates() {
    printf("\nList of Candidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s - %d Votes\n", i + 1, candidates[i].name, candidates[i].votes);
    }
}
void registerVoters() {
    printf("Enter number of voters: ");
    scanf("%d", &voterCount);
    for (int i = 0; i < voterCount; i++) {
        printf("Voter %d Name: ", i + 1);
        scanf(" %[^\n]", voters[i].name);
        printf("Voter ID: ");
        scanf("%s", voters[i].voterID);
        printf("Set Password: ");
        scanf("%s", voters[i].password);
        voters[i].hasVoted = 0;
    }
}
void viewVoters() {
    printf("\nList of Registered Voters:\n");
    for (int i = 0; i < voterCount; i++) {
        printf("%d. Name: %s, Voter ID: %s\n", i + 1, voters[i].name, voters[i].voterID);
    }
}
int verifyVoter(char id[], char pass[]) {
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].voterID, id) == 0 && strcmp(voters[i].password, pass) == 0) {
            if (voters[i].hasVoted) {
                printf("You have already voted!\n");
                return -1;
            }
            return i;
        }
    }
    printf("Invalid Voter ID or Password!\n");
    return -1;
}
void castVote(int voterIndex) {
    char voteName[50];
    printf("Vote for: ");
    scanf(" %[^\n]", voteName);
    for (int i = 0; i < candidateCount; i++) {
        if (strcmp(candidates[i].name, voteName) == 0) {
            candidates[i].votes++;
            voters[voterIndex].hasVoted = 1;
            printf("Vote recorded successfully!\n");
            return;
        }
    }
    printf("Invalid candidate name!\n");
}
void displayResults() {
    printf("\nElection Results:\n");
    int maxVotes = 0, winnerIndex = 0;
    for (int i = 0; i < candidateCount; i++) {
        printf("%s - %d Votes\n", candidates[i].name, candidates[i].votes);
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        }
    }
    printf("\nWinner: %s -%d\n", candidates[winnerIndex].name,candidates[winnerIndex].votes);
    printf("\n Congratulations: %s \n", candidates[winnerIndex].name);
}
int main() 
{
    int choice;
    do {
        printf("\nVoting System Menu:\n");
        printf("1.Manage Candidates\n");
        printf("2.Manage Voters\n");
        printf("3.Start Voting\n");
        printf("4.Display Results\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                printf("\n1.Add Candidates\n2.View Candidates\nEnter choice: ");
                int candChoice;
                scanf("%d", &candChoice);
                if (candChoice == 1) addCandidates();
                else if (candChoice == 2) viewCandidates();
                break;
            case 2:
                printf("\n1.Register Voters\n2.View Voters\nEnter choice: ");
                int voterChoice;
                scanf("%d", &voterChoice);
                if (voterChoice == 1) registerVoters();
                else if (voterChoice == 2) viewVoters();
                break;
            case 3:
                for (int i = 0; i < voterCount; i++) {
                    char id[10], pass[20];
                    printf("\nVoter %d:\nEnter Voter ID: ", i + 1);
                    scanf("%s", id);
                    printf("Enter Password: ");
                    scanf("%s", pass);
                    int voterIndex = verifyVoter(id, pass);
                    if (voterIndex != -1) {
                        castVote(voterIndex);
                    }
                }
                break;
            case 4:
                displayResults();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}