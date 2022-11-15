using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class DustTrail : MonoBehaviour
{
    [SerializeField] ParticleSystem dustEffect;

    bool isPlaying;

    void OnCollisionEnter2D(Collision2D other) 
    {
        if (other.gameObject.tag == "Ground")
        {
            dustEffect.Play();
            isPlaying = true;
        }    
    }

    void OnCollisionExit2D(Collision2D other) 
    {
        if (other.gameObject.tag == "Ground" && isPlaying)
        {
            dustEffect.Stop();
            isPlaying = false;
        }    
    }
}
