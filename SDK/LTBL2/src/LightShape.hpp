#pragma once

#include "Utils.hpp"

namespace ltbl
{

	//////////////////////////////////////////////////////////////////////////
	/// \brief Shape which can block light
	//////////////////////////////////////////////////////////////////////////
	class LightShape : public priv::QuadtreeOccupant, public priv::BaseLight, public sf::Drawable
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		/// \brief Ctor
		//////////////////////////////////////////////////////////////////////////
		LightShape();

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the number of points
		/// \param pointCount New number of points
		//////////////////////////////////////////////////////////////////////////
		void setPointCount(unsigned int pointCount);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the number of points
		/// \return Number of points
		//////////////////////////////////////////////////////////////////////////
		unsigned int getPointCount() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the position of a point
		/// \param index Index of the point to change, in range [0 .. getPointCount()-1]
		/// \param point New position of the point
		//////////////////////////////////////////////////////////////////////////
		void setPoint(unsigned int index, const sf::Vector2f& point);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the position of a point
		/// \param index Index of the point to get, in range [0 .. getPointCount()-1]
		/// \return Position of the index-th point
		//////////////////////////////////////////////////////////////////////////
		sf::Vector2f getPoint(unsigned int index) const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the color of the shape
		/// \param color New color of the shape
		//////////////////////////////////////////////////////////////////////////
		void setColor(const sf::Color& color);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the color of the shape
		/// \return Color of the shape
		//////////////////////////////////////////////////////////////////////////
		const sf::Color& getColor() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the combined transform of the shape
		/// \return Transform combining the position/rotation/scale/origin
		//////////////////////////////////////////////////////////////////////////
		const sf::Transform& getTransform() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the position of the shape
		/// \param position New position
		//////////////////////////////////////////////////////////////////////////
		void setPosition(const sf::Vector2f& position);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the position of the shape
		/// \param x X coordinate of the new position
		/// \param y Y coordinate of the new position
		//////////////////////////////////////////////////////////////////////////
		void setPosition(float x, float y);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Move the shape
		/// \param movement Offset
		//////////////////////////////////////////////////////////////////////////
		void move(const sf::Vector2f& movement);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Move the shape
		/// \param x X offset
		/// \param y Y offset
		//////////////////////////////////////////////////////////////////////////
		void move(float x, float y);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the position of the shape
		/// \return Current position
		//////////////////////////////////////////////////////////////////////////
		const sf::Vector2f& getPosition() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the rotation of the shape
		/// \param angle New rotation, in degrees
		//////////////////////////////////////////////////////////////////////////
		void setRotation(float angle);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Rotate the shape
		/// \param angle Angle of rotation, in degrees
		//////////////////////////////////////////////////////////////////////////
		void rotate(float angle);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the rotation of the shape
		/// \return Current rotation, in degrees
		//////////////////////////////////////////////////////////////////////////
		float getRotation() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the scale of the shape
		/// \param scale New scale factors
		//////////////////////////////////////////////////////////////////////////
		void setScale(const sf::Vector2f& scale);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the scale of the shape
		/// \param x New horizontal scale factor
		/// \param y New vertical scale factor
		//////////////////////////////////////////////////////////////////////////
		void setScale(float x, float y);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Scale of the shape
		/// \param scale Scale factors
		//////////////////////////////////////////////////////////////////////////
		void scale(const sf::Vector2f& scale);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Scale of the shape
		/// \param x Horizontal scale factor
		/// \param y Vertical scale factor
		//////////////////////////////////////////////////////////////////////////
		void scale(float x, float y);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the scale of the shape
		/// \return Current scale factors
		//////////////////////////////////////////////////////////////////////////
		const sf::Vector2f& getScale() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the origin of the shape
		/// \param origin New origin
		//////////////////////////////////////////////////////////////////////////
		void setOrigin(const sf::Vector2f& origin);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the origin of the shape
		/// \param x X coordinate of the new origin
		/// \param y Y coordinate of the new origin
		//////////////////////////////////////////////////////////////////////////
		void setOrigin(float x, float y);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the origin of the shape
		/// \return Current origin
		//////////////////////////////////////////////////////////////////////////
		const sf::Vector2f& getOrigin() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set if the light render over the shape
		/// \param renderLightOver True to render the light over the shape, false hide the shape in the shadow
		//////////////////////////////////////////////////////////////////////////
		void setRenderLightOver(bool renderLightOver);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Do the light render over the shape ?
		/// \return True if the light is rendered over the shape, false otherwise
		//////////////////////////////////////////////////////////////////////////
		bool renderLightOver() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the AABB box of the shape
		/// \return The AABB box
		//////////////////////////////////////////////////////////////////////////
		sf::FloatRect getAABB() const override;

		bool receiveShadow() const;
		void setReceiveShadow(bool receive);

	private:
		//////////////////////////////////////////////////////////////////////////
		/// \brief Draw the shape
		/// \param target The render target to apply the shape on
		/// \param states The render states to apply to the shape on render
		//////////////////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::ConvexShape mShape; ///< The shape data
		bool mRenderLightOver; ///< Do light render over the shape ?
		bool recieve_shadow_;
	};

} // namespace ltbl