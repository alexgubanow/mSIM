using Newtonsoft.Json;

namespace simulation
{
    [JsonObject(MemberSerialization.OptIn)]
    public class Load : Observable
    {
        public Load()
        {
            Name = "";
            lps = new LoadedPoints[1] { new LoadedPoints() };
            les = new LoadedElems[1] { new LoadedElems()};
        }

        private string _Name;

        [JsonProperty]
        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }

        private LoadedPoints[] _lps;

        [JsonProperty]
        public LoadedPoints[] lps { get { return _lps; } set { _lps = value; RaisePropertyChanged("lps"); } }

        private LoadedElems[] _les;

        [JsonProperty]
        public LoadedElems[] les { get { return _les; } set { _les = value; RaisePropertyChanged("les"); } }
    }

    public enum loadType { force, displ }

    public enum loadDirect { vert, x, y, z }
}