#ifndef Magnum_Math_Vector4_h
#define Magnum_Math_Vector4_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class @ref Magnum::Math::Vector4, function @ref Magnum::Math::planeEquation()
 */

#include "Magnum/Math/Vector3.h"

namespace Magnum { namespace Math {

/**
@brief Four-component vector
@tparam T   Data type

See @ref matrix-vector for brief introduction.
@see @ref Magnum::Vector4, @ref Magnum::Vector4i, @ref Magnum::Vector4ui,
    @ref Magnum::Vector4d
@configurationvalueref{Magnum::Math::Vector4}
*/
template<class T> class Vector4: public Vector<4, T> {
    public:
        /**
         * @brief Pad vector to four-component one
         *
         * If size of @p a is smaller than 4, it is padded from right with
         * @p xyz for first three component and @p w for fourth component,
         * otherwise it's cut.
         * @see @ref pad(const Vector<otherSize, T>&, T)
         */
        template<std::size_t otherSize> constexpr static Vector4<T> pad(const Vector<otherSize, T>& a, T xyz, T w) {
            return {0 < otherSize ? a[0] : xyz,
                    1 < otherSize ? a[1] : xyz,
                    2 < otherSize ? a[2] : xyz,
                    3 < otherSize ? a[3] : w};
        }

        /** @copydoc Vector::Vector(ZeroInitT) */
        constexpr /*implicit*/ Vector4(ZeroInitT = ZeroInit) noexcept
            /** @todoc remove workaround when doxygen is sane */
            #ifndef DOXYGEN_GENERATING_OUTPUT
            : Vector<4, T>{ZeroInit}
            #endif
            {}

        /** @copydoc Vector::Vector(NoInitT) */
        explicit Vector4(NoInitT) noexcept
            /** @todoc remove workaround when doxygen is sane */
            #ifndef DOXYGEN_GENERATING_OUTPUT
            : Vector<4, T>{NoInit}
            #endif
            {}

        /** @copydoc Vector::Vector(T) */
        constexpr explicit Vector4(T value) noexcept: Vector<4, T>(value) {}

        /**
         * @brief Constructor
         *
         * @f[
         *      \boldsymbol v = \begin{pmatrix} x \\ y \\ z \\ w \end{pmatrix}
         * @f]
         */
        constexpr /*implicit*/ Vector4(T x, T y, T z, T w) noexcept: Vector<4, T>(x, y, z, w) {}

        /**
         * @brief Constructor
         *
         * @f[
         *      \boldsymbol v = \begin{pmatrix} v_x \\ v_y \\ v_z \\ w \end{pmatrix}
         * @f]
         */
        constexpr /*implicit*/ Vector4(const Vector3<T>& xyz, T w) noexcept: Vector<4, T>(xyz[0], xyz[1], xyz[2], w) {}

        /** @copydoc Vector::Vector(const Vector<size, U>&) */
        template<class U> constexpr explicit Vector4(const Vector<4, U>& other) noexcept: Vector<4, T>(other) {}

        /** @brief Construct vector from external representation */
        template<class U, class V = decltype(Implementation::VectorConverter<4, T, U>::from(std::declval<U>()))> constexpr explicit Vector4(const U& other): Vector<4, T>(Implementation::VectorConverter<4, T, U>::from(other)) {}

        /** @brief Copy constructor */
        constexpr /*implicit*/ Vector4(const Vector<4, T>& other) noexcept: Vector<4, T>(other) {}

        /**
         * @brief X component
         *
         * @see @ref r()
         */
        T& x() { return (*this)[0]; }
        constexpr T x() const { return (*this)[0]; }    /**< @overload */

        /**
         * @brief Y component
         *
         * @see @ref g()
         */
        T& y() { return (*this)[1]; }
        constexpr T y() const { return (*this)[1]; }    /**< @overload */

        /**
         * @brief Z component
         *
         * @see @ref b()
         */
        T& z() { return (*this)[2]; }
        constexpr T z() const { return (*this)[2]; }    /**< @overload */

        /**
         * @brief W component
         *
         * @see @ref a()
         */
        T& w() { return (*this)[3]; }
        constexpr T w() const { return (*this)[3]; }    /**< @overload */

        /**
         * @brief R component
         *
         * Equivalent to @ref x().
         */
        T& r() { return x(); }
        constexpr T r() const { return x(); }           /**< @overload */

        /**
         * @brief G component
         *
         * Equivalent to @ref y().
         */
        T& g() { return y(); }
        constexpr T g() const { return y(); }           /**< @overload */

        /**
         * @brief B component
         *
         * Equivalent to @ref z().
         */
        T& b() { return z(); }
        constexpr T b() const { return z(); }           /**< @overload */

        /**
         * @brief A component
         *
         * Equivalent to @ref w().
         */
        T& a() { return w(); }
        constexpr T a() const { return w(); }           /**< @overload */

        /**
         * @brief XYZ part of the vector
         * @return First three components of the vector
         *
         * @see @ref swizzle(), @ref rgb()
         */
        Vector3<T>& xyz() { return Vector3<T>::from(Vector<4, T>::data()); }
        constexpr const Vector3<T> xyz() const { return {x(), y(), z()}; } /**< @overload */

        /**
         * @brief RGB part of the vector
         * @return First three components of the vector
         *
         * Equivalent to @ref xyz().
         * @see @ref swizzle()
         */
        Vector3<T>& rgb() { return xyz(); }
        constexpr const Vector3<T> rgb() const { return xyz(); } /**< @overload */

        /**
         * @brief XY part of the vector
         * @return First two components of the vector
         *
         * @see @ref swizzle()
         */
        Vector2<T>& xy() { return Vector2<T>::from(Vector<4, T>::data()); }
        constexpr const Vector2<T> xy() const { return {x(), y()}; } /**< @overload */

        MAGNUM_VECTOR_SUBCLASS_IMPLEMENTATION(4, Vector4)
};

/** @relatesalso Vector4
@brief Create a plane equation from three points

Assuming the three points form a triangle in a counter-clockwise winding,
creates a plane equation in the following form: @f[
    ax + by + cz + d = 0
@f]

The first three coefficients describe the *scaled* normal
@f$ \boldsymbol{n} = (a, b, c)^T @f$ and are calculated using a cross product.
The coefficient @f$ d @f$ is calculated using a dot product with the normal
@f$ \boldsymbol{n} @f$ using the first point in order to satisfy the equation
when assigning @f$ \boldsymbol{p_i} @f$ to @f$ x @f$, @f$ y @f$, @f$ z @f$. @f[
    \begin{array}{rcl}
        \boldsymbol{n} & = & (\boldsymbol{p_1} - \boldsymbol{p_0}) \times (\boldsymbol{p_2} - \boldsymbol{p_0}) \\
        d & = & - \boldsymbol{n} \cdot \boldsymbol{p_0}
    \end{array}
@f]
@see @ref planeEquation(const Vector3<T>&, const Vector3<T>&), @ref cross(),
    @ref dot()
*/
template<class T> Vector4<T> planeEquation(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2) {
    const Vector3<T> normal = Math::cross(p1 - p0, p2 - p0).normalized();
    return {normal, -Math::dot(normal, p0)};
}


/** @relatesalso Vector4
@brief Create a plane equation from a normal and a point

Creates a plane equation in the following form: @f[
    ax + by + cz + d = 0
@f]

The first three coefficients describe the *scaled* normal
@f$ \boldsymbol{n} = (a, b, c)^T @f$, the coefficient @f$ d @f$ is calculated
using a dot product with the normal @f$ \boldsymbol{n} @f$ using the point
@f$ \boldsymbol{p} @f$ in order to satisfy the equation when assigning
@f$ \boldsymbol{p} @f$ to @f$ x @f$, @f$ y @f$, @f$ z @f$. @f[
    d = - \boldsymbol{n} \cdot \boldsymbol{p}
@f]
@see @ref planeEquation(const Vector3<T>&, const Vector3<T>&, const Vector3<T>&),
    @ref dot()
*/
template<class T> Vector4<T> planeEquation(const Vector3<T>& normal, const Vector3<T>& point) {
    return {normal, -Math::dot(normal, point)};
}

#ifndef DOXYGEN_GENERATING_OUTPUT
MAGNUM_VECTORn_OPERATOR_IMPLEMENTATION(4, Vector4)
#endif

namespace Implementation {
    template<class T> struct TypeForSize<4, T> { typedef Math::Vector4<typename T::Type> Type; };

    template<class T> struct StrictWeakOrdering<Vector4<T>>: StrictWeakOrdering<Vector<4, T>> {};
}

}}

#endif
