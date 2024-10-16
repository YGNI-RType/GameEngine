/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Callback.hpp
*/

#pragma once

#include <functional>
#include <memory>

namespace ecs::system::event {

/**
 * @brief Abstract base class for event callbacks.
 *
 * This class provides an interface for different types of callbacks used in
 * event handling. Derived classes must implement the `exec` method to handle
 * specific events.
 */
class Base;
class Callback {
public:
    /**
     * @brief Virtual destructor for the Callback class.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Callback() = default;

    /**
     * @brief Executes the callback with the given event.
     *
     * @param event The event to process.
     */
    virtual void exec(const Base &event) const = 0;
};

/**
 * @brief Callback implementation for member function callbacks.
 *
 * This class wraps a member function callback and an instance of the class
 * that contains the member function. When executed, it invokes the member
 * function on the given event.
 *
 * @tparam T The type of the class that owns the member function.
 * @tparam Type The type of the event to process.
 */
template <typename T, typename Type>
class MethodCallback : public Callback {
public:
    using CallbackMethod = void (T::*)(Type &);

    /**
     * @brief Constructs a MethodCallback instance.
     *
     * @param instance The instance of the class that contains the member
     * function.
     * @param callbackMethod Pointer to the member function to be called.
     */
    MethodCallback(T &instance, CallbackMethod callbackMethod);

    /**
     * @brief Executes the member function callback with the given event.
     *
     * Casts the base event to the specific type and invokes the member function
     * on the instance with the casted event.
     *
     * @param event The event to process.
     */
    void exec(const Base &event) const override;

private:
    T &m_instance;                   ///< Reference to the instance of the class containing the
                                     ///< member function.
    CallbackMethod m_callbackMethod; ///< Pointer to the member function.
};

/**
 * @brief Callback implementation for lambda function callbacks.
 *
 * This class wraps a lambda function callback. When executed, it invokes the
 * lambda function with the given event.
 *
 * @tparam Type The type of the event to process.
 */
template <typename Type>
class LambdaCallback : public Callback {
public:
    /**
     * @brief Constructs a LambdaCallback instance.
     *
     * @param callback The lambda function to be called.
     */
    LambdaCallback(std::function<void(Type &)> callback);

    /**
     * @brief Executes the lambda function callback with the given event.
     *
     * Casts the base event to the specific type and invokes the lambda function
     * with the casted event.
     *
     * @param event The event to process.
     */
    void exec(const Base &event) const override;

private:
    std::function<void(Type &)> m_callback; ///< The lambda function callback.
};

} // namespace ecs::system::event

#include "Callback.inl"
