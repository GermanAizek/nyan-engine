#include "LightSystem.hpp"
#include <thread>

namespace ltbl
{

	LightSystem::LightSystem(sf::RenderTexture& normalTexture, sf::RenderTexture& specularTexture, bool useNormals)
		: mPenumbraTexture()
		, mUnshadowShader()
		, mLightOverShapeShader()
		, mNormalsShader()
		, mLightShapeQuadtree(sf::FloatRect())
		, mLightPointEmissionQuadtree(sf::FloatRect())
		, mPointEmissionLights()
		, mDirectionEmissionLights()
		, mLightShapes()
		, mLightTempTexture()
		, mEmissionTempTexture()
		, mEmissionTempSpecTexture()
		, mAntumbraTempTexture()
		, mCompositionTexture()
		, mNormalsTexture(normalTexture)
		, mSpecularTexture(specularTexture)
		, mSpecTempTexture()
		, mSpecularCompTexture()
		, mDirectionEmissionRange(1000.0f)
		, mDirectionEmissionRadiusMultiplier(1.1f)
		, mAmbientColor(sf::Color(16, 16, 16))
		, mUseNormals(useNormals)
	{
		// Load Texture
		mPenumbraTexture.loadFromMemory(priv::penumbraTexture, (sizeof(priv::penumbraTexture) / sizeof(*priv::penumbraTexture)));
		mPenumbraTexture.setSmooth(true);

		// Load Shaders
		mUnshadowShader.loadFromMemory(priv::unshadowFragment, sf::Shader::Fragment);
		mLightOverShapeShader.loadFromMemory(priv::lightOverShapeFragment, sf::Shader::Fragment);
		mNormalsShader.loadFromMemory(priv::normalFragment, sf::Shader::Fragment);
		mSpecularShader.loadFromMemory(priv::specularFragment, sf::Shader::Fragment);
	}

	void LightSystem::create(const sf::FloatRect& rootRegion, const sf::Vector2u& imageSize)
	{
		for (auto & lpe : mPointEmissionLights)
		{
			removeLight(lpe);
		}

		for (auto & lde : mDirectionEmissionLights)
		{
			removeLight(lde);
		}

		for (auto & lsh : mLightShapes)
		{
			removeShape(lsh);
		}

		// Quadtrees
		mLightShapeQuadtree.create(rootRegion, 6, 6);
		mLightPointEmissionQuadtree.create(rootRegion, 6, 6);

		update(imageSize);
	}

	void LightSystem::render(sf::RenderTarget& target)
	{
		sf::View view = target.getView();
		if (target.getSize() != mLightTempTexture.getSize())
		{
			update(target.getSize());
		}


			mLightShapeQuadtree.update();
			mLightPointEmissionQuadtree.update();

		const sf::FloatRect viewBounds = sf::FloatRect(view.getCenter() - view.getSize() * 0.5f, view.getSize());

			mSpecularCompTexture.clear(sf::Color::Black);
			mSpecularCompTexture.setView(mSpecularCompTexture.getDefaultView());

			mCompositionTexture.clear(mAmbientColor);
			mCompositionTexture.setView(mCompositionTexture.getDefaultView());

			mLightTempTexture.setView(view);
			mSpecTempTexture.setView(view);

			// --- Point lights

			std::vector<priv::QuadtreeOccupant*> lightShapes;
		const sf::Sprite lightTempSprite(mLightTempTexture.getTexture());
		const sf::Sprite specTempSprite(mSpecTempTexture.getTexture());

			// Query lights
			std::vector<priv::QuadtreeOccupant*> viewPointEmissionLights;
			mLightPointEmissionQuadtree.query(viewBounds, viewPointEmissionLights);

			for (const auto& occupant : viewPointEmissionLights)
			{
				LightPointEmission* light = static_cast<LightPointEmission*>(occupant);
				if (light != nullptr && light->isTurnedOn())
				{
					// Query shapes
					lightShapes.clear();
					mLightShapeQuadtree.query(light->getAABB(), lightShapes);

					// Render light
					light->render(view, mLightTempTexture, mAntumbraTempTexture, mSpecTempTexture,
						mUnshadowShader, mLightOverShapeShader, lightShapes,
						mUseNormals, mNormalsShader, mSpecularShader, mEmissionTempTexture, mEmissionTempSpecTexture);
					mCompositionTexture.draw(lightTempSprite, sf::BlendAdd);
					mSpecularCompTexture.draw(specTempSprite, sf::BlendAdd);
				}
			}

			//----- Direction lights

		const float shadowExtension = priv::vectorMagnitude(view.getSize() * -0.5f) * mDirectionEmissionRadiusMultiplier;
		const sf::Vector2f extendedBounds = sf::Vector2f(1.f, 1.f) * std::max(viewBounds.width, viewBounds.height) * mDirectionEmissionRadiusMultiplier;
			sf::FloatRect extendedViewBounds = priv::rectFromBounds(-extendedBounds, extendedBounds + sf::Vector2f(mDirectionEmissionRange, 0.0f));

			std::vector<priv::QuadtreeOccupant*> viewLightShapes;

			for (const auto& light : mDirectionEmissionLights)
			{
				// Create light shape
				sf::ConvexShape directionShape = priv::shapeFromRect(extendedViewBounds);
				directionShape.setPosition(view.getCenter());
				directionShape.setRotation(light->getCastAngle());

				// Query shapes
				viewLightShapes.clear();
				mLightShapeQuadtree.query(directionShape, viewLightShapes);

				// Render light
				light->render(view, mLightTempTexture, mAntumbraTempTexture, mUnshadowShader, viewLightShapes, shadowExtension);
				mCompositionTexture.draw(sf::Sprite(mLightTempTexture.getTexture()), sf::BlendAdd);
			}

			mCompositionTexture.display();


		const auto sz = view.getSize();
		sf::Sprite sprite = sf::Sprite(mCompositionTexture.getTexture());
		mSpecularCompTexture.draw(sprite, sf::BlendMultiply);
		mSpecularCompTexture.display();
		sprite.setPosition(view.getCenter() - view.getSize() / 2.f);
		sprite.setScale(sz.x / target.getSize().x, sz.y / target.getSize().y);
		target.draw(sprite, sf::BlendMultiply);
		sprite.setTexture(mSpecularCompTexture.getTexture());
		target.draw(sprite, sf::BlendAdd);
	}

	LightShape* LightSystem::createLightShape()
	{
		LightShape* shape = new LightShape();
		mLightShapeQuadtree.addOccupant(shape);
		mLightShapes.push_back(shape);
		return shape;
	}

	LightShape* LightSystem::createLightShape(const sf::RectangleShape& shape)
	{
		LightShape* lightShape = createLightShape();
		lightShape->setPointCount(4u);
		lightShape->setPoint(0u, { 0.f, 0.f });
		lightShape->setPoint(1u, { shape.getSize().x, 0.f });
		lightShape->setPoint(2u, shape.getSize());
		lightShape->setPoint(3u, { 0.f, shape.getSize().y });
		lightShape->setPosition(shape.getPosition());
		lightShape->setOrigin(shape.getOrigin());
		lightShape->setRotation(shape.getRotation());
		lightShape->setScale(shape.getScale());
		return lightShape;
	}

	LightShape* LightSystem::createLightShape(const sf::ConvexShape& shape)
	{
		LightShape* lightShape = createLightShape();
		const unsigned int pointCount = shape.getPointCount();
		lightShape->setPointCount(pointCount);
		for (unsigned int i = 0; i < pointCount; i++)
		{
			lightShape->setPoint(i, shape.getPoint(i));
		}
		lightShape->setPosition(shape.getPosition());
		lightShape->setOrigin(shape.getOrigin());
		lightShape->setRotation(shape.getRotation());
		lightShape->setScale(shape.getScale());
		return lightShape;
	}

	LightShape* LightSystem::createLightShape(const sf::CircleShape& shape)
	{
		LightShape* lightShape = createLightShape();
		unsigned int pointCount = shape.getPointCount();
		lightShape->setPointCount(pointCount);
		for (unsigned int i = 0; i < pointCount; i++)
		{
			lightShape->setPoint(i, shape.getPoint(i));
		}
		lightShape->setPosition(shape.getPosition());
		lightShape->setOrigin(shape.getOrigin());
		lightShape->setRotation(shape.getRotation());
		lightShape->setScale(shape.getScale());
		return lightShape;
	}

	LightShape* LightSystem::createLightShape(const sf::FloatRect& rect)
	{
		LightShape* lightShape = createLightShape();
		lightShape->setPointCount(4u);
		lightShape->setPoint(0u, { 0.f, 0.f });
		lightShape->setPoint(1u, { rect.width, 0.f });
		lightShape->setPoint(2u, { rect.width, rect.height });
		lightShape->setPoint(3u, { 0.f, rect.height });
		lightShape->setPosition(rect.left, rect.top);
		return lightShape;
	}

	LightShape* LightSystem::createLightShape(const sf::Sprite& sprite)
	{
		LightShape* lightShape = createLightShape();
		lightShape->setPointCount(4u);
		lightShape->setPoint(0u, { 0.f, 0.f });
		lightShape->setPoint(1u, { sprite.getTextureRect().width * 1.f, 0.f });
		lightShape->setPoint(2u, { sprite.getTextureRect().width * 1.f, sprite.getTextureRect().height * 1.f });
		lightShape->setPoint(3u, { 0.f, sprite.getTextureRect().height * 1.f });
		lightShape->setPosition(sprite.getPosition());
		lightShape->setOrigin(sprite.getOrigin());
		lightShape->setRotation(sprite.getRotation());
		lightShape->setScale(sprite.getScale());
		return lightShape;
	}

	void LightSystem::removeShape(LightShape* shape)
	{
		const auto itr = std::find(mLightShapes.begin(), mLightShapes.end(), shape);
		//auto itr = mLightShapes.find(shape);
		if (itr != mLightShapes.end())
		{
			mLightShapeQuadtree.removeOccupant(*itr);
			mLightShapes.erase(itr);
			delete shape;
		}
	}

	LightPointEmission* LightSystem::createLightPointEmission()
	{
		LightPointEmission* light = new LightPointEmission();
		mLightPointEmissionQuadtree.addOccupant(light);
		mPointEmissionLights.push_back(light);
		return light;
	}

	void LightSystem::removeLight(LightPointEmission* light)
	{
		auto itr = std::find(mPointEmissionLights.begin(), mPointEmissionLights.end(), light);
		if (itr != mPointEmissionLights.end())
		{
			mLightPointEmissionQuadtree.removeOccupant(*itr);
			mPointEmissionLights.erase(itr);
			delete light;
		}
	}

	LightDirectionEmission* LightSystem::createLightDirectionEmission()
	{
		LightDirectionEmission* light = new LightDirectionEmission();
		mDirectionEmissionLights.push_back(light);
		return light;
	}

	void LightSystem::removeLight(LightDirectionEmission* light)
	{
		//auto itr = mDirectionEmissionLights.find(light);
		const auto itr = std::find(mDirectionEmissionLights.begin(), mDirectionEmissionLights.end(), light);
		if (itr != mDirectionEmissionLights.end())
		{
			mDirectionEmissionLights.erase(itr);
			delete light;
		}
	}

	void LightSystem::setDirectionEmissionRange(float range)
	{
		mDirectionEmissionRange = range;
	}

	float LightSystem::getDirectionEmissionRange() const
	{
		return mDirectionEmissionRange;
	}

	void LightSystem::setDirectionEmissionRadiusMultiplier(float multiplier)
	{
		mDirectionEmissionRadiusMultiplier = multiplier;
	}

	float LightSystem::getDirectionEmissionRadiusMultiplier() const
	{
		return mDirectionEmissionRadiusMultiplier;
	}

	void LightSystem::setAmbientColor(const sf::Color& color)
	{
		mAmbientColor = color;
	}

	const sf::Color& LightSystem::getAmbientColor() const
	{
		return mAmbientColor;
	}

	bool LightSystem::useNormals() const
	{
		return mUseNormals;
	}

	void LightSystem::update(sf::Vector2u const& size)
	{
		mUnshadowShader.setUniform("penumbraTexture", mPenumbraTexture);
		mNormalsShader.setUniform("normalsTexture", mNormalsTexture.getTexture());
		mNormalsShader.setUniform("lightTexture", sf::Shader::CurrentTexture);
		mSpecularShader.setUniform("normalTexture", mNormalsTexture.getTexture());
		mSpecularShader.setUniform("specularTexture", mSpecularTexture.getTexture());
		mSpecularShader.setUniform("lightTexture", sf::Shader::CurrentTexture);

		if (size.x != 0 && size.y != 0)
		{
			mLightTempTexture.create(size.x, size.y);
			mEmissionTempTexture.create(size.x, size.y);
			mEmissionTempSpecTexture.create(size.x, size.y);
			mAntumbraTempTexture.create(size.x, size.y);
			mCompositionTexture.create(size.x, size.y);
			mNormalsTexture.create(size.x, size.y);
			mSpecularTexture.create(size.x, size.y);
			mSpecularCompTexture.create(size.x, size.y);
			mSpecTempTexture.create(size.x, size.y);

			mNormalsShader.setUniform("targetSize", sf::Glsl::Vec2(size.x * 1.f, size.y * 1.f));
			mSpecularShader.setUniform("targetSize", sf::Glsl::Vec2(size.x * 1.f, size.y * 1.f));
			mLightOverShapeShader.setUniform("targetSizeInv", sf::Glsl::Vec2(1.0f / size.x, 1.0f / size.y));
		}
	}

	sf::Texture& LightSystem::getPenumbraTexture()
	{
		return mPenumbraTexture;
	}

	sf::Shader& LightSystem::getUnshadowShader()
	{
		return mUnshadowShader;
	}

	sf::Shader& LightSystem::getLightOverShapeShader()
	{
		return mLightOverShapeShader;
	}

	sf::Shader& LightSystem::getNormalsShader()
	{
		return mNormalsShader;
	}

	sf::Shader& LightSystem::getSpecularShader()
	{
		return mSpecularShader;
	}

	sf::RenderTexture& LightSystem::getNormalTexture() const
	{
		return mNormalsTexture;
	}

	sf::RenderTexture& LightSystem::getSpecularTexture() const
	{
		return mSpecularTexture;
	}

	const sf::RenderTexture& LightSystem::getLightCompTexture() const
	{
		return mCompositionTexture;
	}

	const sf::RenderTexture& LightSystem::getSpecCompTexture() const
	{
		return mSpecularCompTexture;
	}
} // namespace ltbl