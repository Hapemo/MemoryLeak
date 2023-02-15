using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class ScriptTemplate : BaseScript
    {
        public override void PreInit(int _id) {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        public void Init(int _id) {
            
        }

        public void Update(int _id) {

        }

        public void Exit(int _id) {
            
        }
    }
}
