using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class FragmentScript : BaseScript
    {
        public override void PreInit(int _id)
        {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        public void Init(int _id) {
            
        }

        public void Update(int _id) {
            //if (InternalCalls.EntitiesCollided("Boat", "fragment1drop", "Level1"))
            //{ 
            
            //}
        }

        public void Exit(int _id) {
            
        }
    }
}
