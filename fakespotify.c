#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song{
    char title[50];
    struct Song* next;
    struct Song* prev;
}Song;

typedef struct playlist{
    Song* first;
    int elemcount;
}Playlist;

void CreatePlaylist(Playlist* playlist){
    playlist->first=NULL;
    playlist->elemcount=0;
}

void AddPlaylist(Playlist* playlist, char* newsong){
    Song* song=(Song*)malloc(sizeof(Song));
    song->next=playlist->first;
    playlist->first=song;
    strcpy(playlist->first->title, newsong);
    playlist->elemcount++;
}

void RemovePlaylist(Playlist* playlist){
    Song* song=playlist->first;
    playlist->first=song->next;
    free(song);
    playlist->elemcount--;
}

void NowPlaying(Playlist* playlist, int scroll){
    Song* song=playlist->first;
    for (int i = 0; i < scroll; i++){
        song=song->next;
        song->prev=song;
    }
    
    printf("Now %s is playing\n", song->title);
    printf("Next:%s\n", song->next->title);
    printf("Previous:%s\n", song->prev->title);
}

int main(){

    Playlist myplaylist;

    CreatePlaylist(&myplaylist);

    for (int i = 0; i <5; i++){
        AddPlaylist(&myplaylist, "Listed Song");
    }

    Song* ptr=myplaylist.first;
    int i=1;
    while(ptr!=NULL){
        printf("%s %d\n", ptr->title, i);
        i++;
        ptr=ptr->next;
    }

    printf("Over!\n");
    printf("There are %d songs in the list!\n", myplaylist.elemcount);

    NowPlaying(&myplaylist, 4);
    return 0;
}
