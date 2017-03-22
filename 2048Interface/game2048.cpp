#include "game2048.h"
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include <QtWidgets/QMessageBox>



using namespace std;

   /* void Game_AI::set_exec_copie(Game* exec){
       exec_copie = exec;
    }*/

    int Game2048::get_response(){
        return this->response;
    }
    void Game2048::set_response(int response){
        this->response = response;
    }

    QString Game2048::get_score(){
        return QString::number(score);
    }

    QString Game2048::get_0_0(){
        if(grid[0][0]==0)
            return "";
        return QString::number(grid[0][0]);
    }

    QString Game2048::get_0_1(){
        if(grid[0][1]==0)
            return "";
        return QString::number(grid[0][1]);
    }

    QString Game2048::get_0_2(){
        if(grid[0][2]==0)
            return "";
        return QString::number(grid[0][2]);
    }

    QString Game2048::get_0_3(){
        if(grid[0][3]==0)
            return "";
        return QString::number(grid[0][3]);
    }

    QString Game2048::get_1_0(){
        if(grid[1][0]==0)
            return "";
        return QString::number(grid[1][0]);
    }

    QString Game2048::get_1_1(){
        if(grid[1][1]==0)
            return "";
        return QString::number(grid[1][1]);
    }

    QString Game2048::get_1_2(){
        if(grid[1][2]==0)
            return "";
        return QString::number(grid[1][2]);
    }

    QString Game2048::get_1_3(){
        if(grid[1][3]==0)
            return "";
        return QString::number(grid[1][3]);
    }

    QString Game2048::get_2_0(){
        if(grid[2][0]==0)
            return "";
        return QString::number(grid[2][0]);
    }

    QString Game2048::get_2_1(){
        if(grid[2][1]==0)
            return "";
        return QString::number(grid[2][1]);
    }

    QString Game2048::get_2_2(){
        if(grid[2][2]==0)
            return "";
       return QString::number(grid[2][2]);
    }

    QString Game2048::get_2_3(){
        if(grid[2][3]==0)
            return "";
        return QString::number(grid[2][3]);
    }

    QString Game2048::get_3_0(){
        if(grid[3][0]==0)
            return "";
        return QString::number(grid[3][0]);
    }

    QString Game2048::get_3_1(){
        if(grid[3][1]==0)
            return "";
       return QString::number(grid[3][1]);
    }

    QString Game2048::get_3_2(){
        if(grid[3][2]==0)
            return "";
        return QString::number(grid[3][2]);
    }

    QString Game2048::get_3_3(){
        if(grid[3][3]==0)
            return "";
        return QString::number(grid[3][3]);
    }

    void Game2048::load_grid(){
        cellChnaged();
    }

    void Game2048::key_press_up()
    {
      control = 'w';
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }
    void Game2048::key_press_down()
    {
      control = 's';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }
    void Game2048::key_press_right()
    {
      control = 'd';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }
    void Game2048::key_press_left()
    {
      control = 'a';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }

    void Game2048::key_press_undo()
    {
      control = 'u';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }

    void Game2048::key_press_restart()
    {
      control = 'r';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }

    void Game2048::key_press_quit()
    {
      control = 'q';
      cout<<control;
      this->logic_flow();
      this->game_end_check();
      cellChnaged();
    }

    int random_index(int x)
    {
        int index;
        index=rand()%x+0;

    return index;
    }

    /*not yet*/void Game2048::logic_flow()
    {

      switch(control)
      {
          case 'w':
          case 'a':
          case 's':
          case 'd':
              this->backup_grid();
              this->reOrganize_grid();
              this->update_grid();
              this->reOrganize_grid();
              this->PlusGrandeCase();
              usleep(1000*160);

              if(this->full()&&User_updating)
              {
                  response=-1;
                  break;
              }
              else if(this->move_action())
              {
                  this->invoque_number();
                  break;
              }
              else
              {
                  response=0;
                  break;
              }

          case 'u':
              if(this->move_action())
                score-=plus;
              this->undo();
              break;


          case 'r':
              this->init_grid();
              score=0;
              break;

          case 'q':
              response=-1;
              break;
      }
    }

    void Game2048::game_end_check()
    {
      if(max==win)
      {
        this->display_win_screen();

      }

      else if(response==-1)
      {
        this->display_loser_screen();
      }

      if(response==-1)
      {
        exit(0);
      }
    }

    void Game2048::init_grid()
    {
      int i,j;

      //plus=0;
      score=0;
      max=0;

        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                grid[i][j]=0;

        i=random_index(4);
        j=random_index(4);

            grid[i][j]=2;

        i=random_index(4);
        j=random_index(4);

            grid[i][j]=2;
    }

    void Game2048::backup_grid()
    {
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    bgrid[i][j]=grid[i][j];
    }


    void Game2048::reOrganize_grid()
    {

        switch(control)
        {
            case 'w':
                        for(int i=0;i<4;i++)
                            for(int j=0;j<4;j++)
                            {
                                if(!grid[j][i])
                                {
                                    for(int k=j+1;k<4;k++)
                                        if(grid[k][i])
                                        {
                                            grid[j][i]=grid[k][i];
                                            grid[k][i]=0;
                                            break;
                                        }
                                }

                            }break;

            case 's':
                        for(int i=0;i<4;i++)
                            for(int j=3;j>=0;j--)
                            {
                                if(!grid[j][i])
                                {
                                    for(int k=j-1;k>=0;k--)
                                        if(grid[k][i])
                                        {
                                            grid[j][i]=grid[k][i];
                                            grid[k][i]=0;
                                            break;
                                        }
                                }

                            }break;
            case 'a':
                        for(int i=0;i<4;i++)
                            for(int j=0;j<4;j++)
                            {
                                if(!grid[i][j])
                                {
                                    for(int k=j+1;k<4;k++)
                                        if(grid[i][k])
                                        {
                                            grid[i][j]=grid[i][k];
                                            grid[i][k]=0;
                                            break;
                                        }
                                }

                            }break;


            case 'd':
                        for(int i=0;i<4;i++)
                            for(int j=3;j>=0;j--)
                            {
                                if(!grid[i][j])
                                {
                                    for(int k=j-1;k>=0;k--)
                                        if(grid[i][k])
                                        {
                                            grid[i][j]=grid[i][k];
                                            grid[i][k]=0;
                                            break;
                                        }
                                }

                            }break;

        }
    }


    void Game2048::update_grid()
    {
        plus=0;
        User_updating=1;

        switch(control)
        {
            case 'w':
                        for(int i=0;i<4;i++)
                            for(int j=0;j<3;j++)
                            {
                                if(grid[j][i]&&grid[j][i]==grid[j+1][i])
                                {
                                    User_updating=0;
                                    grid[j][i]+=grid[j+1][i];
                                    grid[j+1][i]=0;
                                    plus+=(((log2(grid[j][i]))-1)*grid[j][i]);
                                    score+=(((log2(grid[j][i]))-1)*grid[j][i]);

                                }
                            }break;

            case 's':
                        for(int i=0;i<4;i++)
                            for(int j=3;j>0;j--)
                            {
                                if(grid[j][i]&&grid[j][i]==grid[j-1][i])
                                {
                                    User_updating=0;
                                    grid[j][i]+=grid[j-1][i];
                                    grid[j-1][i]=0;
                                    plus+=(((log2(grid[j][i]))-1)*grid[j][i]);
                                    score+=(((log2(grid[j][i]))-1)*grid[j][i]);
                                }
                            }break;

            case 'a':
                        for(int i=0;i<4;i++)
                            for(int j=0;j<3;j++)
                            {
                                if(grid[i][j]&&grid[i][j]==grid[i][j+1])
                                {
                                    User_updating=0;
                                    grid[i][j]+=grid[i][j+1];
                                    grid[i][j+1]=0;
                                    plus+=((log2(grid[i][j]))-1)*grid[i][j];
                                    score+=((log2(grid[i][j]))-1)*grid[i][j];
                                }
                            }break;

            case 'd':
                        for(int i=0;i<4;i++)
                            for(int j=3;j>0;j--)
                            {
                                if(grid[i][j]&&grid[i][j]==grid[i][j-1])
                                {
                                    User_updating=0;
                                    grid[i][j]+=grid[i][j-1];
                                    grid[i][j-1]=0;
                                    plus+=((log2(grid[i][j]))-1)*grid[i][j];
                                    score+=(((log2(grid[i][j]))-1)*grid[i][j]);
                                }
                            }break;


        }



    }


    void Game2048::invoque_number()
    {
            int i,j,k;

            do
            {
                i=random_index(4);
                j=random_index(4);
                k=random_index(10);

            }while(grid[i][j]);



            if(k<2)
                grid[i][j]=4;

            else
                grid[i][j]=2;


    }


    void Game2048::PlusGrandeCase()
    {
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(grid[i][j]>max)
                    max=grid[i][j];
    }

    /*not yet*/int Game2048::full()
    {
        int k=1;

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
                if(!grid[i][j])
                    k=0;

            }
    return k;
    }

    void Game2048::undo()
    {
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    grid[i][j]=bgrid[i][j];
    }

    /*not yet*/int Game2048::move_action()
    {
        int k=0;

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(bgrid[i][j]!=grid[i][j])
                {
                    k=1;
                    break;
                }
    return k;
    }

    /****************************************Displays***********************************/

    /*not yet*/void Game2048::display_win_screen()
    {
        QMessageBox msgBox;
        msgBox.setText("You win!");
        msgBox.setInformativeText("Do you want to replay?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
              response=0;
              this->key_press_restart();
              break;
          case QMessageBox::No:
              exit(0);
              break;
          default:
              response=0;
              this->key_press_restart();
              break;
        }
    }

    /*not yet*/void Game2048::display_loser_screen()
    {
        QMessageBox msgBox;
        msgBox.setText("You lost!");
        msgBox.setInformativeText("Do you want to replay?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
              response=0;
              this->key_press_restart();
              //screen->start_grid();

              break;
          case QMessageBox::No:
              exit(0);
              //this->key_press_quit();
              break;
          default:
              response=0;
              this->key_press_restart();
              break;
        }
    }


