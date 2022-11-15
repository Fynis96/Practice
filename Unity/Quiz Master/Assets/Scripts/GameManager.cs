using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{

    Quiz quizObject;
    EndScreen endScreen;
    void Start()
    {
        quizObject = FindObjectOfType<Quiz>();
        endScreen = FindObjectOfType<EndScreen>();

        quizObject.gameObject.SetActive(true);
        endScreen.gameObject.SetActive(false);
    }

    void Update()
    {
        if(quizObject.isComplete)
        {
            quizObject.gameObject.SetActive(false);
            endScreen.gameObject.SetActive(true);
            endScreen.ShowFinalScore();
        }
    }

    public void OnReplayLevel()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}
