using Newtonsoft.Json;

namespace simulation
{
    [JsonObject(MemberSerialization.OptIn)]
    public class Material : Observable
    {
        public Material()
        {
            Name = "";
            L = 0;
            h = 0;
            b = 0;
            ro = 0;
            E = 0;
        }

        private string _Name;

        [JsonProperty]
        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }

        private float _L;

        [JsonProperty]
        public float L { get { return _L; } set { _L = value; RaisePropertyChanged("L"); } }

        private float _b;

        [JsonProperty]
        public float b { get { return _b; } set { _b = value; RaisePropertyChanged("b"); } }

        private float _h;

        [JsonProperty]
        public float h { get { return _h; } set { _h = value; RaisePropertyChanged("h"); } }

        private float _ro;

        [JsonProperty]
        public float ro { get { return _ro; } set { _ro = value; RaisePropertyChanged("ro"); } }

        private float _E;

        [JsonProperty]
        public float E { get { return _E; } set { _E = value; RaisePropertyChanged("E"); } }
    }
}