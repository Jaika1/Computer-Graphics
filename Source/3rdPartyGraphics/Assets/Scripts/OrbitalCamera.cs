using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbitalCamera : MonoBehaviour
{
    public Transform TargetTransform;
    public float MaxFollowDistance = 5.0f;
    public float HeightAbove = 2.0f;

    private HumanControls controlScheme;
    private Vector2 lookValue;
    private Vector3 angle;
    private LayerMask playerLayer;

    // Start is called before the first frame update
    void Awake()
    {
        controlScheme = new HumanControls();
        controlScheme.Enable();
        angle = transform.eulerAngles;
        Cursor.lockState = CursorLockMode.Locked;
        playerLayer = LayerMask.GetMask("Player");
    }

    // Update is called once per frame
    void Update()
    {
        lookValue = controlScheme.Humanoid.Look.ReadValue<Vector2>();

        if (lookValue.magnitude > 0.0f)
        {
            angle.x = Mathf.Clamp(angle.x - lookValue.y, -80, 85);
            angle.y += lookValue.x;

            transform.rotation = Quaternion.Euler(angle);
        }

        Vector3 orbitalPos = TargetTransform.position + (HeightAbove * Vector3.up);
        float fDist = MaxFollowDistance;
        Ray r = new Ray(orbitalPos, -transform.forward);
        RaycastHit info;
        if (Physics.Raycast(r, out info, MaxFollowDistance, ~playerLayer))
        {
            fDist = info.distance - 0.1f;
        }
        transform.position = orbitalPos - transform.forward * fDist;
    }
}
