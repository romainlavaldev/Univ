pthread_mutex_t mutex_monitor = PTHREAD_MUTEX_INITIALIZER;

boolean_t ecr = FALSE;
int cpt_lect = 0;
pthread_cond_t cond_lect = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_ecr = PTHREAD_COND_INITIALIZER;

void debut_lecture(){
    pthread_mutex_lock(&mutex_monitor);

    if(ecr){
        pthread_cond_wait(&cond_lect, &mutex_monitor);
        pthread_cond_signal(&cond_lect); //Reveil en cascade de tous les lecteurs
    }

    pthread_mutex_unlock(&mutex_monitor);
}

void fin_lecture(){
    pthread_mutex_lock(&mutex_monitor);

    cpt_lect --;
    if(cpt_lect == 0){
        pthread_cond_signal(&cond_ecr);
    }

    pthread_mutex_unlock(&mutex_monitor);
}

void debut_ecriture(){
    pthread_mutex_lock(&mutex_monitor);

    if(ecr || cpt_lect > 0){
        pthread_cond_wait(&cond_ecr, &mutex_monitor);
    }

    ecr = TRUE;
    
    pthread_mutex_unlock(&mutex_monitor);
}

void fin_eecriture(){
    pthread_mutex_lock(&mutex_monitor);

    if(cpt_lect > 0){
        pthread_cond_signal(&cond_lect);
    }else{
        pthread_cond_signal(&cond_ecr);
    }

    ecr = FALSE;
    
    pthread_mutex_unlock(&mutex_monitor);
}