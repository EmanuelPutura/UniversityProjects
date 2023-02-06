class HttpOutMessage<C> {
  static const String okServerMessage = 'ok';

  final C collection;
  final String serverResponse;
  final bool online;

  HttpOutMessage(this.collection, this.serverResponse, this.online);
}
