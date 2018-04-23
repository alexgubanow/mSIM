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

        private double _L;

        [JsonProperty]
        public double L { get { return _L; } set { _L = value; RaisePropertyChanged("L"); } }

        private double _b;

        [JsonProperty]
        public double b { get { return _b; } set { _b = value; RaisePropertyChanged("b"); } }

        private double _h;

        [JsonProperty]
        public double h { get { return _h; } set { _h = value; RaisePropertyChanged("h"); } }

        private double _ro;

        [JsonProperty]
        public double ro { get { return _ro; } set { _ro = value; RaisePropertyChanged("ro"); } }

        private double _E;

        [JsonProperty]
        public double E { get { return _E; } set { _E = value; RaisePropertyChanged("E"); } }
    }
}