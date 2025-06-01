#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

namespace gazebo
{
  class TrafficLightController : public WorldPlugin
  {
    physics::WorldPtr world;
    event::ConnectionPtr updateConnection;
    common::Time lastUpdate;
    double cycleDuration = 3.0;
    int state = 0;

  public:
    void Load(physics::WorldPtr _world, sdf::ElementPtr /*_sdf*/) override
    {
      world = _world;
      lastUpdate = world->SimTime();
      updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&TrafficLightController::OnUpdate, this));
    }

    void OnUpdate()
    {
      common::Time now = world->SimTime();
      if ((now - lastUpdate).Double() > cycleDuration)
      {
        state = (state + 1) % 3;
        UpdateLight();
        lastUpdate = now;
      }
    }

    void UpdateLight()
    {
      auto model = world->ModelByName("traffic_light");
      if (!model) return;

      auto link = model->GetLink("light_post");
      if (!link) return;

      for (auto visual : link->GetVisuals())
      {
        if (visual->Name().find("green_light") != std::string::npos)
          visual->SetVisible(state == 0);
        if (visual->Name().find("yellow_light") != std::string::npos)
          visual->SetVisible(state == 1);
        if (visual->Name().find("red_light") != std::string::npos)
          visual->SetVisible(state == 2);
      }
    }
  };

  GZ_REGISTER_WORLD_PLUGIN(TrafficLightController)
}