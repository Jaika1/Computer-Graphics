// GENERATED AUTOMATICALLY FROM 'Assets/InputSystem/HumanControls.inputactions'

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Utilities;

public class @HumanControls : IInputActionCollection, IDisposable
{
    public InputActionAsset asset { get; }
    public @HumanControls()
    {
        asset = InputActionAsset.FromJson(@"{
    ""name"": ""HumanControls"",
    ""maps"": [
        {
            ""name"": ""Humanoid"",
            ""id"": ""b5fe741e-529d-4ff7-a84a-73affe926c6c"",
            ""actions"": [
                {
                    ""name"": ""Look"",
                    ""type"": ""Value"",
                    ""id"": ""1cce0bd9-644f-4ce1-ab4e-1035a248dd92"",
                    ""expectedControlType"": ""Vector2"",
                    ""processors"": """",
                    ""interactions"": """"
                },
                {
                    ""name"": ""Move"",
                    ""type"": ""Value"",
                    ""id"": ""1140c440-9a6a-4d40-a068-82f5b0ad470f"",
                    ""expectedControlType"": ""Vector2"",
                    ""processors"": """",
                    ""interactions"": """"
                }
            ],
            ""bindings"": [
                {
                    ""name"": """",
                    ""id"": ""d481e55c-e271-4900-845e-ac16388e42bb"",
                    ""path"": ""<Mouse>/delta"",
                    ""interactions"": """",
                    ""processors"": ""ScaleVector2(x=0.1,y=0.1)"",
                    ""groups"": """",
                    ""action"": ""Look"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""caa1dce1-bffa-4b61-8255-58df22c3332b"",
                    ""path"": ""<Gamepad>/rightStick"",
                    ""interactions"": """",
                    ""processors"": ""ScaleVector2(x=0.5,y=0.5)"",
                    ""groups"": """",
                    ""action"": ""Look"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""f01fb2e6-98f5-4303-965f-4748a8c6e823"",
                    ""path"": ""<Gamepad>/leftStick"",
                    ""interactions"": """",
                    ""processors"": ""StickDeadzone"",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": ""WASD"",
                    ""id"": ""3dd708a6-c97a-4fca-92bf-54cab2d49237"",
                    ""path"": ""2DVector"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": true,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": ""up"",
                    ""id"": ""7e279b21-259e-402b-a821-607542148357"",
                    ""path"": ""<Keyboard>/w"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""down"",
                    ""id"": ""b2f48aa0-a4c0-4882-a013-967d85d9a595"",
                    ""path"": ""<Keyboard>/s"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""left"",
                    ""id"": ""5329ed3b-b3cf-4341-87a7-f79b6f77e1ad"",
                    ""path"": ""<Keyboard>/a"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                },
                {
                    ""name"": ""right"",
                    ""id"": ""42b05570-e9d0-40fe-b2a2-36e7a391511a"",
                    ""path"": ""<Keyboard>/d"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Move"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": true
                }
            ]
        }
    ],
    ""controlSchemes"": []
}");
        // Humanoid
        m_Humanoid = asset.FindActionMap("Humanoid", throwIfNotFound: true);
        m_Humanoid_Look = m_Humanoid.FindAction("Look", throwIfNotFound: true);
        m_Humanoid_Move = m_Humanoid.FindAction("Move", throwIfNotFound: true);
    }

    public void Dispose()
    {
        UnityEngine.Object.Destroy(asset);
    }

    public InputBinding? bindingMask
    {
        get => asset.bindingMask;
        set => asset.bindingMask = value;
    }

    public ReadOnlyArray<InputDevice>? devices
    {
        get => asset.devices;
        set => asset.devices = value;
    }

    public ReadOnlyArray<InputControlScheme> controlSchemes => asset.controlSchemes;

    public bool Contains(InputAction action)
    {
        return asset.Contains(action);
    }

    public IEnumerator<InputAction> GetEnumerator()
    {
        return asset.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void Enable()
    {
        asset.Enable();
    }

    public void Disable()
    {
        asset.Disable();
    }

    // Humanoid
    private readonly InputActionMap m_Humanoid;
    private IHumanoidActions m_HumanoidActionsCallbackInterface;
    private readonly InputAction m_Humanoid_Look;
    private readonly InputAction m_Humanoid_Move;
    public struct HumanoidActions
    {
        private @HumanControls m_Wrapper;
        public HumanoidActions(@HumanControls wrapper) { m_Wrapper = wrapper; }
        public InputAction @Look => m_Wrapper.m_Humanoid_Look;
        public InputAction @Move => m_Wrapper.m_Humanoid_Move;
        public InputActionMap Get() { return m_Wrapper.m_Humanoid; }
        public void Enable() { Get().Enable(); }
        public void Disable() { Get().Disable(); }
        public bool enabled => Get().enabled;
        public static implicit operator InputActionMap(HumanoidActions set) { return set.Get(); }
        public void SetCallbacks(IHumanoidActions instance)
        {
            if (m_Wrapper.m_HumanoidActionsCallbackInterface != null)
            {
                @Look.started -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnLook;
                @Look.performed -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnLook;
                @Look.canceled -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnLook;
                @Move.started -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnMove;
                @Move.performed -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnMove;
                @Move.canceled -= m_Wrapper.m_HumanoidActionsCallbackInterface.OnMove;
            }
            m_Wrapper.m_HumanoidActionsCallbackInterface = instance;
            if (instance != null)
            {
                @Look.started += instance.OnLook;
                @Look.performed += instance.OnLook;
                @Look.canceled += instance.OnLook;
                @Move.started += instance.OnMove;
                @Move.performed += instance.OnMove;
                @Move.canceled += instance.OnMove;
            }
        }
    }
    public HumanoidActions @Humanoid => new HumanoidActions(this);
    public interface IHumanoidActions
    {
        void OnLook(InputAction.CallbackContext context);
        void OnMove(InputAction.CallbackContext context);
    }
}
