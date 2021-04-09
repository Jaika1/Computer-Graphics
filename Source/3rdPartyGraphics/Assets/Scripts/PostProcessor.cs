using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PostProcessor : MonoBehaviour
{
    public Material[] PostProcessingLayers;

    // Start is called before the first frame update
    private void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        Array.ForEach(PostProcessingLayers, m => Graphics.Blit(source, destination, m));
    }
}
