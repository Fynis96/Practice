using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Timer : MonoBehaviour
{
    [SerializeField] float timeToShowCorrectAnswer = 10f;
    [SerializeField] float timeToCompleteQuestion = 30f;
    public bool loadNextQuestion = true;
    public bool isAnsweringQuestion = false;
    public float fillFraction; 

    float timerValue;
    void Update()
    {
        UpdateTimer();
    }

    public void CancelTimer()
    {
        timerValue = 0;
    }

    void UpdateTimer()
    {
        timerValue -= Time.deltaTime;

        if(isAnsweringQuestion)
        {
            if(timerValue <= 0)
            {
                isAnsweringQuestion = false;
                timerValue = timeToShowCorrectAnswer;
            }
            else 
            {
                fillFraction = timerValue / timeToCompleteQuestion;
            }
        }
        else
        {
            if(timerValue <= 0)
            {
                isAnsweringQuestion = true;
                timerValue = timeToCompleteQuestion;
                loadNextQuestion = true;
            }
            else
            {
                fillFraction = timerValue / timeToShowCorrectAnswer;
            }
        }
    }
}
