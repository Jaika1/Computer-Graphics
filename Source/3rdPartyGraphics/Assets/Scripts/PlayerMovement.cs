using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    public Animator AnimationController;
    public Transform cameraTransform;

    HumanControls controls;
    CharacterController charCon;
    Vector2 moveInput;

    // Start is called before the first frame update
    void Start()
    {
        charCon = GetComponent<CharacterController>();
        controls = new HumanControls();
        controls.Enable();
    }

    // Update is called once per frame
    void Update()
    {
        moveInput = controls.Humanoid.Move.ReadValue<Vector2>();
        AnimationController.SetFloat("Forward", moveInput.y);
        AnimationController.SetFloat("Turn", moveInput.x);
        //AnimationController.SetFloat("Sign", Mathf.Sign(moveVec.y));

        if (moveInput.magnitude > 0.0f)
        {
            transform.rotation = Quaternion.Euler(0.0f, cameraTransform.rotation.eulerAngles.y, 0.0f);
        }
    }

    private void FixedUpdate()
    {
        Vector3 moveVec = (moveInput.x * transform.right + moveInput.y * transform.forward) * 4.0f;

        if (!charCon.isGrounded)
            moveVec += Physics.gravity;

        charCon.Move(moveVec * Time.fixedDeltaTime);
    }
}
