using Newtonsoft.Json;

namespace simulation.ViewModel
{
    [JsonObject(MemberSerialization.OptIn)]
    class load : Observable
    {
        public load()
        {
            Name = "";
        }

        [JsonProperty]
        private string _Name;

        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }
    }
}
