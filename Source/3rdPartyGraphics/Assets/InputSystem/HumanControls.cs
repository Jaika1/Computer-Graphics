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
                }
            ]
        }
    ],
    ""controlSchemes"": []
}");
        // Humanoid
        m_Humanoid = asset.FindActionMap("Humanoid", throwIfNotFound: true);
        m_Humanoid_Look = m_Humanoid.FindAction("Look", throwIfNotFound: true);
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
    public struct HumanoidActions
    {
        private @HumanControls m_Wrapper;
        public HumanoidActions(@HumanControls wrapper) { m_Wrapper = wrapper; }
        public InputAction @Look => m_Wrapper.m_Humanoid_Look;
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
            }
            m_Wrapper.m_HumanoidActionsCallbackInterface = instance;
            if (instance != null)
            {
                @Look.started += instance.OnLook;
                @Look.performed += instance.OnLook;
                @Look.canceled += instance.OnLook;
            }
        }
    }
    public HumanoidActions @Humanoid => new HumanoidActions(this);
    public interface IHumanoidActions
    {
        void OnLook(InputAction.CallbackContext context);
    }
}
